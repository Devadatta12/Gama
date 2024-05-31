#pragma once
#include "zmq.hpp"
#include "Events.h"
#include "thread"

namespace gama {

    class PeerListenerTask{
    public:
        PeerListenerTask(int port);
        void Start();
        void Run();
        void Stop();
    private:
        zmq::context_t m_SubscriberContext;
        zmq::socket_t m_SubscriberSocket;
        int m_SubscriberPort;
        volatile bool m_IsShutdown;
    };

    class Peer{
    public:
        Peer(int publishPort, int sub1, int sub2, int sub3);
        void Start();
        void Send(Event& event);
        void Shutdown();
    private:
        zmq::context_t m_PubContext;
        zmq::socket_t m_PubSocket;
        PeerListenerTask m_Peer1;
        PeerListenerTask m_Peer2;
        PeerListenerTask m_Peer3;
        std::thread* m_Executor1;
        std::thread* m_Executor2;
        std::thread* m_Executor3;
        int m_PublishPort;
        volatile bool m_IsShutdown;
    };
}