#pragma once
#include "Components.h"
#include "Entities.h"
#include "Physics.h"
#include "unordered_map"
#include "ScriptManager.h"

namespace gama {

    class CollisionInfo{
    public:
        long CharacterUUID = -1;
        long CollidedUUID = -1;
        float CollisionX = 0;
        float CollisionY = 0;
        int CollidedType = -1;
    };

    class CollisionSolver{
    public:
        CollisionSolver()= default;
        void Resolve(CollisionInfo collision);
        void AddScripting(ScriptManager* sm){r_ScriptManager = sm;};
    private:
        ScriptManager* r_ScriptManager;
    };

    class CollisionSystem: public EventHandler{
    public:
        explicit CollisionSystem(Timeline* anchor): m_Solver(new CollisionSolver()),
                m_CollisionTimeline(anchor){};
        void Initialize();
        void Detect();
        void OnEvent(Event& event) override;
        void Shutdown();
        void AddScripting(ScriptManager* sm){m_Solver->AddScripting(sm);};
        ~CollisionSystem(){delete m_Solver;};
    private:
        std::unordered_map<long, CollisionMesh*> m_Collidables;
        std::unordered_map<long, CollisionMesh*> m_Actors;
        CollisionSolver* m_Solver;
        Timeline* m_CollisionTimeline;
        int64_t m_LastDetectionTime;
    };

}