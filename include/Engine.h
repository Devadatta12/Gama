#pragma once

#include <cstdint>
#include <mutex>

#include "Collisions.h"
#include "Physics.h"
#include "Input.h"
#include "World.h"
#include "Network.h"
#include "Timelines.h"
#include "Rendering.h"
#include "TimeKeeper.h"
#include "Replays.h"
#include "Events.h"
#include "ScriptManager.h"
#include <libplatform/libplatform.h>
#include <iostream>
#include "v8helpers.h"
#include <v8.h>
#include <cstdio>

#define DEFAULT_CLIENT_UPDATE_RATE 17
#define DEFAULT_SERVER_UPDATE_RATE 17

namespace gama{

    class Specifications{

    };

    class Engine{
    public:
        Engine();
        void Start();
        void Run();
        void Stop();
    private:
        World* m_World;
        ScoringSystem* m_ScoringSystem;
        EventManager* m_EventMgr;
        PhysicsEngine* m_PhysicsEngine;
        RenderingEngine* m_RenderingEngine;
        CollisionSystem* m_CollisionSystem;
        TimeKeeper* m_TimeKeeper;
        NetworkMgr* m_NetworkMgr;
        InputSystem* m_InputSystem;
        Timeline* m_Timeline;
        int64_t m_LastTime;
    };
}