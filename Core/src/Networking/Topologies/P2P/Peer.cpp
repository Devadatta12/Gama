#include "Peer.h"
#include "Messages.h"
#include "thread"
#include "iostream"


namespace gama {
    Peer::Peer(int publishPort, int sub1, int sub2, int sub3) : m_Peer1(sub1),
                                        m_Peer2(sub2), m_Peer3(sub3) {

        m_PubContext =  zmq::context_t(1);
        m_PubSocket = zmq::socket_t(m_PubContext, zmq::socket_type::pub);
        m_PublishPort = publishPort;
        m_Executor1 = nullptr;
        m_Executor2 = nullptr;
        m_Executor3 = nullptr;
        m_IsShutdown = true;
    }

    void Peer::Start() {
        m_PubSocket.bind("tcp://*:"+std::to_string(m_PublishPort));
        m_Peer1.Start();
        m_Executor1 = new std::thread(&PeerListenerTask::Run, std::ref(m_Peer1));
        m_Peer2.Start();
        m_Executor2 = new std::thread(&PeerListenerTask::Run, std::ref(m_Peer2));
        m_Peer3.Start();
        m_Executor3 = new std::thread(&PeerListenerTask::Run, std::ref(m_Peer3));
        m_IsShutdown = false;
    }

    void Peer::Send(Event &event) {
        if (!m_IsShutdown){
            switch (event.type) {
                case Event::EventLocalUpdate:
                {
                    zmq::message_t reply = zmq::message_t();
                    m_PubSocket.send(EngineMessages::SendPeerEvent(event), zmq::send_flags::none);
                    break;
                }
                case Event::EventClientLeft:
                {
                    zmq::message_t reply = zmq::message_t();
                    m_PubSocket.send(EngineMessages::SendPeerExit(event), zmq::send_flags::none);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Peer::Shutdown() {
        m_IsShutdown = true;
        m_Peer1.Stop();
        m_Peer2.Stop();
        m_Peer3.Stop();
    }


    PeerListenerTask::PeerListenerTask(int port) {
        m_SubscriberContext = zmq::context_t(1);
        m_SubscriberSocket = zmq::socket_t(m_SubscriberContext, zmq::socket_type::sub);
        m_SubscriberPort = port;
        m_IsShutdown = true;
    }

    void PeerListenerTask::Start() {
        m_IsShutdown = false;
    }

    void PeerListenerTask::Run() {
        if (!m_IsShutdown){
            m_SubscriberSocket.connect("tcp://localhost:"+std::to_string(m_SubscriberPort));
            const char *filter = "PEER";
            m_SubscriberSocket.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));
            while (!m_IsShutdown){
                zmq::message_t peerUpdate;
                m_SubscriberSocket.recv(peerUpdate, zmq::recv_flags::none);
                std::string serializedMsg = peerUpdate.to_string();
                switch (serializedMsg.at(5)) {
                    case 'U':
                    {
                        std::string update = serializedMsg.substr(6);
                        Event characterUpdate(Event::EventCharacterUpdate, 0);
                        characterUpdate.worldEvent.message = new std::string(update);
                        EventManager::GetInstance()->Execute(characterUpdate);
                        break;
                    }
                    case 'D':
                    {
                        std::string deletedEntity = serializedMsg.substr(6);
                        Event characterDel(Event::EventCharacterDelete, 0);
                        characterDel.worldEvent.message = new std::string(deletedEntity);
                        EventManager::GetInstance()->Execute(characterDel);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    void PeerListenerTask::Stop() {
        m_IsShutdown = true;
    }
}