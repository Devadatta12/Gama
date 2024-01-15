#include "Network.h"
#include "iostream"

namespace gama {

    NetworkMgr::NetworkMgr(NetworkProps &networkProps) {
        EventManager::GetInstance()->Register(this, NETWORK_EVENTS);
        if (networkProps.topology == NetworkProps::CLIENT_SERVER){
            m_Topology = new ClientServerTopology(networkProps.role,
                                                  networkProps.eventPort, networkProps.statusPort);
        } else {
            m_Topology = new Peer2PeerTopology(networkProps.pubPort, networkProps.peerPort1,
                                               networkProps.peerPort2, networkProps.peerPort3);
        }

    }

    void NetworkMgr::Initialize() {
        if (m_Topology != nullptr){
            m_Topology->Initialize();
        }
    }

    void NetworkMgr::OnEvent(Event& event) {
        if (m_Topology != nullptr){
            m_Topology->Handle(event);
        }
    }

    void NetworkMgr::Shutdown() {
        if (m_Topology != nullptr){
            m_Topology->Shutdown();
        }
    }
}