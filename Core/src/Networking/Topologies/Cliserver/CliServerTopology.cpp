#include "Topologies.h"
#include "iostream"


namespace gama{

    ClientServerTopology::ClientServerTopology(int role, int eventPort, int statusPort) {
        m_Role = role;
        if (m_Role == SERVER){
            m_Server = new Server(eventPort, statusPort);
        } else {
            m_Client = new Client(eventPort, statusPort);
        }
    }

    void ClientServerTopology::Initialize() {
        if (m_Role == CLIENT && m_Client != nullptr){
            m_Client->Start();
        } else if (m_Role == SERVER && m_Server != nullptr){
            m_Server->Start();
        }
    }

    void ClientServerTopology::Handle(gama::Event &event) {
        if (m_Role == CLIENT && m_Client != nullptr){
            m_Client->Send(event);
        }
    }

    void ClientServerTopology::Shutdown() {
        if (m_Role == CLIENT && m_Client != nullptr){
            m_Client->Shutdown();
        } else if (m_Role == SERVER && m_Server != nullptr){
            m_Server->Shutdown();
        }
    }
}