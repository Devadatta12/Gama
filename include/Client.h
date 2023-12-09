#pragma once

#include "zmq.hpp"
#include "thread"
#include "Events.h"

namespace gama {

    class StatusTask{
    public:
        explicit StatusTask(int syncPort);
        void Start();
        void Pause(){ m_Paused = true;};
        void Run();
        void Resume(){m_Paused = false;};
        void Stop();
    private:
        zmq::context_t m_StatusContext;
        zmq::socket_t m_StatusSocket;
        Timeline* m_StatusTimeline;
        int64_t m_LastStatusTime;
        int m_StatusPort;
        volatile bool m_IsShutdown;
        volatile bool m_Paused;
    };

    class Client{
    public:
        Client(int eventPort, int statusPort);
        void Start();
        void Send(Event& event);
        void Shutdown();
    private:
        static long _initialize(zmq::message_t& message);
        zmq::context_t m_EventContext;
        zmq::socket_t m_EventSocket;
        StatusTask m_StatusTask;
        std::thread* m_Executor;
        long m_CliId = -1;
        int m_EventPort;
        volatile bool m_IsShutdown;
    };
}
