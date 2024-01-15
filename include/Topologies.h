#pragma once
#include "zmq.hpp"
#include "Events.h"
#include "Messages.h"
#include "Client.h"
#include "Server.h"
#include "Peer.h"



namespace gama {
    class Topology{
    public:
        virtual void Initialize() = 0;
        virtual void Handle(Event& event) = 0;
        virtual void Shutdown() = 0;
    };

    class ClientServerTopology: public Topology{
    public:
        constexpr const static int CLIENT = 1;
        constexpr const static int SERVER = 2;

        ClientServerTopology(int role, int eventPort, int statusPort);
        void Initialize() override;
        void Handle(Event &event) override;
        void Shutdown() override;

    private:
        Client* m_Client = nullptr;
        Server* m_Server = nullptr;
        int m_Role;
    };

    class Peer2PeerTopology: public Topology{
    public:
        Peer2PeerTopology(int pubPort, int subPort1, int subPort2, int subPort3);
        void Initialize() override;
        void Handle(Event &event) override;
        void Shutdown() override;
    private:
        Peer* m_Peer = nullptr;
    };
}