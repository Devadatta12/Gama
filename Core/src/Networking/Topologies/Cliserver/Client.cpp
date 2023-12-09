#include "Client.h"
#include "Messages.h"
#include "Utils.h"

namespace gama {

    Client::Client(int eventPort, int statusPort): m_StatusTask(statusPort){
        m_EventContext = zmq::context_t(1);
        m_EventSocket = zmq::socket_t(m_EventContext, zmq::socket_type::req);
        m_EventPort = eventPort;
        m_Executor = nullptr;
        m_IsShutdown = true;
    }

    void Client::Start() {
        m_EventSocket.connect("tcp://localhost:"+std::to_string(m_EventPort));
        zmq::message_t reply = zmq::message_t();
        m_EventSocket.send(EngineMessages::JoinRequest(), zmq::send_flags::none);
        m_EventSocket.recv(reply, zmq::recv_flags::none);
        m_CliId = _initialize(reply);
        m_StatusTask.Start();
        m_Executor = new std::thread(&StatusTask::Run, std::ref(m_StatusTask));
        m_IsShutdown = false;
    }

    void Client::Send(Event& event){
        if (!m_IsShutdown){
            if (event.type == Event::EventStartReplay){
                std::cout<<"Start Replay"<<std::endl;
                m_StatusTask.Pause();
            } else if(event.type == Event::EventEndReplay){
                m_StatusTask.Resume();
            }
            else{
                zmq::message_t reply = zmq::message_t();
                m_EventSocket.send(EngineMessages::SendUpdateEvent(event), zmq::send_flags::none);
                m_EventSocket.recv(reply, zmq::recv_flags::none);
            }
        }
    }

    void Client::Shutdown() {
        m_IsShutdown = true;
        m_StatusTask.Stop();
    }

    long Client::_initialize(zmq::message_t& message) {
        std::string serializedMessage = message.to_string();
        std::vector<std::string> tokens = tokenize(serializedMessage, "|");
        std::string clientId = tokens[0];
        std::string world = tokens[1];
        // Needs to happen before everything else. Hence 0 priority.
        Event worldEvent(Event::EventCreateWorld, 0);
        worldEvent.worldEvent.message = new std::string(world);
        //std::cout<<"Event: "<<*worldEvent.worldEvent.message<<std::endl;
        // Call World directly to save time.
        EventManager::GetInstance()->Execute(worldEvent);
        return std::stol(clientId);
    }


    StatusTask::StatusTask(int syncPort) {
        m_StatusContext = zmq::context_t(1);
        m_StatusSocket = zmq::socket_t(m_StatusContext, zmq::socket_type::req);
        m_StatusPort = syncPort;
        m_IsShutdown = true;
        m_StatusTimeline = new Timeline(nullptr, 17);
        m_LastStatusTime = m_StatusTimeline->getTime();
        m_Paused = false;
    }

    void StatusTask::Start() {
        m_StatusSocket.connect("tcp://localhost:" + std::to_string(m_StatusPort));
        m_IsShutdown = false;
    }

    void StatusTask::Run() {
        while (!m_IsShutdown){
            int64_t currTime = m_StatusTimeline->getTime();
            int64_t delta = currTime - m_LastStatusTime;
            if (delta < 1){
                continue;
            }
            m_LastStatusTime = currTime;
            if (m_Paused){
                continue;
            }
            zmq::message_t reply = zmq::message_t();
            m_StatusSocket.send(EngineMessages::SyncRequest(), zmq::send_flags::none);
            m_StatusSocket.recv(reply, zmq::recv_flags::none);
            // The status updates need to be executed as soon as possible.
            Event syncWorld(Event::EventSyncWorld, 0);
            syncWorld.worldEvent.message =new std::string(reply.to_string());
            //std::cout<<"Event: "<<*syncWorld.worldEvent.message<<std::endl;
            EventManager::GetInstance()->Execute(syncWorld);
        }
    }

    void StatusTask::Stop() {
        m_IsShutdown = true;
    }
}