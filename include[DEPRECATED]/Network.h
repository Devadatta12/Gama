#pragma once

#include "zmq.hpp"
#include "Topologies.h"
#include "Events.h"
#include "thread"

namespace gama{

    class NetworkProps{
    public:
        constexpr const static int CLIENT_SERVER = 1;
        constexpr const static int P2P = 2;
        int topology = -1;
        int role = -1;
        int eventPort = -1;
        int statusPort = -1;
        int pubPort = -1;
        int peerPort1 = -1;
        int peerPort2 = -1;
        int peerPort3 = -1;
    };

    class NetworkMgr: public EventHandler{
    public:
        explicit NetworkMgr(NetworkProps& networkProps);
        void Initialize();
        void OnEvent(Event& event) override;
        void Shutdown();
    private:
        Topology* m_Topology;
    };
}