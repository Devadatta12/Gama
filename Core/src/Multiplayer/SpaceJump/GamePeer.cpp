#include "Engine.h"
#include "chrono"
#include "iostream"

int main(int argc, char *argv[]){
    const int ADDRESSES[] = {5001, 5002, 5003, 5004};
    if (argc < 2){
        std::cout<<"Usage: ./gamepeer #UNIQUE_PEER_NUMBER#"<<std::endl;
        return 0;
    }
    int peerNumber = std::stoi(std::string(argv[1]));
    int peerIdx = peerNumber - 1;
    int PEERS[3] = {-1, -1, -1};
    int idx = 0;
    for (int i = 0; i < 4; ++i) {
        if (i != peerIdx){
            PEERS[idx++] = ADDRESSES[i];
        }
    }

    gama::NetworkProps networkProps;
    networkProps.pubPort = ADDRESSES[peerIdx];
    networkProps.peerPort1 = PEERS[0];
    networkProps.peerPort2 = PEERS[1];
    networkProps.peerPort3 = PEERS[2];
    networkProps.topology = gama::NetworkProps::P2P;

    auto* m_EventMgr = gama::EventManager::GetInstance();
    auto* m_Timeline = new gama::Timeline(nullptr, 17);
    m_EventMgr->Initialize(m_Timeline);
    auto* m_TimeKeeper = new gama::TimeKeeper();
    m_TimeKeeper->Initialize();
    m_TimeKeeper->Keep(gama::TimeKeeper::WILDCARD, m_Timeline);
    auto* m_PhysicsEngine = new gama::PhysicsEngine(m_Timeline);
    auto* m_CollisionSystem = new gama::CollisionSystem(m_Timeline);
    auto* m_RenderingEngine = new gama::RenderingEngine();
    auto* m_InputSystem = new gama::InputSystem(m_Timeline);
    auto* m_ScoringSystem = new gama::ScoringSystem();
    auto* m_World = new gama::World(m_Timeline, false, peerNumber, "SpaceJump");
    auto* m_NetworkMgr = new gama::NetworkMgr(networkProps);
    long m_LastTime = m_Timeline->getTime();


    m_PhysicsEngine->Initialize();
    m_InputSystem->Initialize();
    m_CollisionSystem->Initialize();

    m_RenderingEngine->Initialize("SpaceJump");
    m_ScoringSystem->Initialize(m_Timeline);
    m_World->Initialize();
    m_NetworkMgr->Initialize();

    while (true){
        m_EventMgr->Dispatch();
        if (!m_RenderingEngine->PollWindow()){
            break;
        }

        m_InputSystem->Poll();
        m_World->Update();
        m_CollisionSystem->Detect();
        m_PhysicsEngine->Simulate();
        m_RenderingEngine->Render();
    }

    m_InputSystem->Shutdown();
    m_RenderingEngine->Shutdown();
    m_PhysicsEngine->Shutdown();
    m_CollisionSystem->Shutdown();
    m_ScoringSystem->Shutdown();
    m_NetworkMgr->Shutdown();
    m_World->Shutdown();

    return 0;
}
