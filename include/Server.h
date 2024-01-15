#pragma once

#include "zmq.hpp"
#include "thread"
#include "Events.h"

namespace gama {

    class EventService{
    public:
        constexpr const static char* ACK = "ACK";
        constexpr const static int ACK_LEN = 3;
        explicit EventService(int eventPort);
        void Start();
        void Run();
        void Stop();
    private:
        zmq::context_t m_EventContext;
        zmq::socket_t m_EventSocket;
        int m_EventPort;
        volatile bool m_IsShutdown;
    };

    class StatusService{
    public:
        explicit StatusService(int statusPort);
        void Start();
        void Run();
        void Stop();
    private:
        zmq::context_t m_StatusContext;
        zmq::socket_t m_StatusSocket;
        int m_StatusPort;
        volatile bool m_IsShutdown;
    };

    class Server{
    public:
        static long CLI_SEQ;
        Server(int eventPort, int statusPort);
        void Start();
        void Shutdown();
    private:
        EventService m_EventService;
        StatusService m_StatusService;
        std::thread* m_EventExecutor;
        std::thread* m_StatusExecutor;
        volatile bool m_IsShutdown;
    };
}