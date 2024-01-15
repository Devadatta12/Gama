#include "Engine.h"
#include "chrono"
#include "iostream"


namespace gama {

    Engine::Engine() {
        m_EventMgr = EventManager::GetInstance();
        m_Timeline = new Timeline(nullptr, 17);
        m_EventMgr->Initialize(m_Timeline);
        m_TimeKeeper = new TimeKeeper();
        m_TimeKeeper->Initialize();
        m_TimeKeeper->Keep(TimeKeeper::WILDCARD, m_Timeline);
        m_PhysicsEngine = new PhysicsEngine(m_Timeline);
        m_CollisionSystem = new CollisionSystem(m_Timeline);
        NetworkProps networkProps;
        m_NetworkMgr = new NetworkMgr(networkProps);
        m_RenderingEngine = new RenderingEngine();
        m_InputSystem = new InputSystem(m_Timeline);
        m_ScoringSystem = new ScoringSystem();
        m_World = new World(m_Timeline, true, 0, "");
        m_LastTime = m_Timeline->getTime();
    }

    void Engine::Start() {
        m_PhysicsEngine->Initialize();
        m_InputSystem->Initialize();
        m_CollisionSystem->Initialize();
        m_NetworkMgr->Initialize();
        m_RenderingEngine->Initialize("");
        m_ScoringSystem->Initialize(m_Timeline);
        m_World->Initialize();
        Event createCharacter(Event::EventCharacterJoin, 0);
        createCharacter.worldEvent.isMyCharacter = true;
        m_World->OnEvent(createCharacter);
    }

    void Engine::Run() {
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
    }

    void Engine::Stop() {

    }
}
