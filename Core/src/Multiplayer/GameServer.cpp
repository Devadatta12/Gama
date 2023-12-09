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
    gama::NetworkProps networkProps;
    networkProps.eventPort = 5556;
    networkProps.statusPort = 5557;
    networkProps.topology = gama::NetworkProps::CLIENT_SERVER;
    networkProps.role = 2;
    auto* m_NetworkMgr = new gama::NetworkMgr(networkProps);
    auto* m_World = new gama::World(m_Timeline, true, 0);
    long m_LastTime = m_Timeline->getTime();

    std::cout<<"Initializing"<<std::endl;


    m_World->Initialize();
    m_NetworkMgr->Initialize();

    std::cout<<"Started"<<std::endl;

    while (true){
        m_EventMgr->Dispatch();
        m_World->Update();
    }


    m_NetworkMgr->Shutdown();
    m_World->Shutdown();

    return 0;
}
