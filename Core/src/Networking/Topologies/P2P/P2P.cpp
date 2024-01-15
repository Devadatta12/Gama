#include "Topologies.h"

namespace gama {

    Peer2PeerTopology::Peer2PeerTopology(int pubPort, int subPort1, int subPort2, int subPort3) {
        m_Peer = new Peer(pubPort, subPort1, subPort2, subPort3);
    }

    void Peer2PeerTopology::Initialize() {
        if (m_Peer != nullptr){
            m_Peer->Start();
        }
    }

    void Peer2PeerTopology::Handle(Event &event) {
        if (m_Peer != nullptr){
            m_Peer->Send(event);
        }
    }

    void Peer2PeerTopology::Shutdown() {
        if (m_Peer != nullptr){
            m_Peer->Shutdown();
        }
    }


}

