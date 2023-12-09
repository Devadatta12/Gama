#include "Engine.h"
#include "chrono"
#include "iostream"

int main(){
    auto* m_EventMgr = gama::EventManager::GetInstance();
    auto* m_Timeline = new gama::Timeline(nullptr, 17);
    m_EventMgr->Initialize(m_Timeline);
    auto* m_TimeKeeper = new gama::TimeKeeper();
    m_TimeKeeper->Initialize();
    m_TimeKeeper->Keep(gama::TimeKeeper::WILDCARD, m_Timeline);
    auto* m_PhysicsEngine = new gama::PhysicsEngine(m_Timeline);
    auto* m_CollisionSystem = new gama::CollisionSystem(m_Timeline);
    gama::NetworkProps networkProps;
    networkProps.eventPort = 5556;
    networkProps.statusPort = 5557;
    networkProps.topology = gama::NetworkProps::CLIENT_SERVER;
    networkProps.role = 1;
    auto* m_NetworkMgr = new gama::NetworkMgr(networkProps);
    auto* m_RenderingEngine = new gama::RenderingEngine();
    auto* m_InputSystem = new gama::InputSystem(m_Timeline);
    auto* m_ScoringSystem = new gama::ScoringSystem();
    auto* m_World = new gama::World(m_Timeline, false, 0);
    auto* m_ReplaySystem = new gama::ReplaySystem();
    long m_LastTime = m_Timeline->getTime();


    m_PhysicsEngine->Initialize();
    m_InputSystem->Initialize();
    m_CollisionSystem->Initialize();

    m_RenderingEngine->Initialize();
    m_ScoringSystem->Initialize(m_Timeline);
    m_World->Initialize();
    m_NetworkMgr->Initialize();
    m_ReplaySystem->Initialize();

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
