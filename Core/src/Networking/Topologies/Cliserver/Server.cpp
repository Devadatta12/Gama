#include "Server.h"
#include "Messages.h"
#include "iostream"

namespace gama {

    long Server::CLI_SEQ = 0;

    Server::Server(int eventPort, int statusPort): m_EventService(eventPort), m_StatusService(statusPort) {
        m_EventExecutor = nullptr;
        m_StatusExecutor = nullptr;
        m_IsShutdown = true;
    }

    void Server::Start() {
        m_EventService.Start();
        m_EventExecutor = new std::thread(&EventService::Run, std::ref(m_EventService));
        m_StatusService.Start();
        m_StatusExecutor = new std::thread(&StatusService::Run, std::ref(m_StatusService));
        m_IsShutdown = false;
    }

    void Server::Shutdown() {
        m_IsShutdown = true;
        m_EventService.Stop();
        m_StatusService.Stop();
    }

    EventService::EventService(int eventPort) {
        m_EventContext = zmq::context_t(2);
        m_EventSocket =  zmq::socket_t(m_EventContext, zmq::socket_type::rep);
        m_EventPort = eventPort;
        m_IsShutdown = true;
    }

    void EventService::Start() {
        m_EventSocket.bind ("tcp://*:" + std::to_string(m_EventPort));
        m_IsShutdown = false;
    }

    void EventService::Run() {
        while (!m_IsShutdown){
            zmq::message_t request = zmq::message_t();
            zmq::message_t reply = zmq::message_t();
            m_EventSocket.recv (request, zmq::recv_flags::none);
            std::string serializedRequest = request.to_string();
            char requestType = serializedRequest.front();
            switch (requestType) {
                case EngineMessages::JOIN:
                {
                    long newClientId = ++Server::CLI_SEQ;
                    Event characterJoin(Event::EventCharacterJoin, 0);
                    EventManager::GetInstance()->Execute(characterJoin);
                    std::string serializedWorld = std::to_string(newClientId)+"|"+*characterJoin.worldEvent.message;
                    reply = zmq::message_t(serializedWorld.size());
                    memcpy (reply.data (), serializedWorld.c_str(), serializedWorld.size());
                    break;
                }
                case EngineMessages::UPDATE_EVENT:
                {
                    reply = zmq::message_t(ACK_LEN);
                    memcpy (reply.data (), ACK, ACK_LEN);
                    Event characterUpdate(Event::EventCharacterUpdate, 0);
                    std::string content = request.to_string().substr(2);
                    characterUpdate.worldEvent.message = new std::string(content);
                    std::cout<<"Event: "<<*characterUpdate.worldEvent.message<<std::endl;
                    EventManager::GetInstance()->Execute(characterUpdate);
                    break;
                }
                case EngineMessages::DELETE:
                {
                    reply = zmq::message_t(ACK_LEN);
                    memcpy (reply.data (), ACK, ACK_LEN);
                    Event characterUpdate(Event::EventCharacterDelete, 0);
                    std::string content = request.to_string().substr(2);
                    characterUpdate.worldEvent.message = new std::string(content);
                    std::cout<<"Event: "<<*characterUpdate.worldEvent.message<<std::endl;
                    EventManager::GetInstance()->Execute(characterUpdate);
                    break;
                }
                default:
                    break;
            }
            m_EventSocket.send(reply, zmq::send_flags::none);
        }
    }

    void EventService::Stop() {
        m_IsShutdown = true;
    }


    StatusService::StatusService(int statusPort) {
        m_StatusContext = zmq::context_t(2);
        m_StatusSocket =  zmq::socket_t(m_StatusContext, zmq::socket_type::rep);
        m_StatusPort = statusPort;
        m_IsShutdown = true;
    }

    void StatusService::Start() {
        m_StatusSocket.bind ("tcp://*:" + std::to_string(m_StatusPort));
        m_IsShutdown = false;
    }

    void StatusService::Run() {
        while (!m_IsShutdown){
            zmq::message_t request = zmq::message_t();
            zmq::message_t reply = zmq::message_t();
            m_StatusSocket.recv (request, zmq::recv_flags::none);
            Event sendWorld(Event::EventSendWorld, 0);
            EventManager::GetInstance()->Execute(sendWorld);
            std::string* serializedWorld = sendWorld.worldEvent.message;
            std::cout<<"Event: "<<*sendWorld.worldEvent.message<<std::endl;
            reply = zmq::message_t(serializedWorld->size());
            memcpy (reply.data (), serializedWorld->c_str(), serializedWorld->size());
            m_StatusSocket.send(reply, zmq::send_flags::none);
        }
    }

    void StatusService::Stop() {
        m_IsShutdown = true;
    }
}