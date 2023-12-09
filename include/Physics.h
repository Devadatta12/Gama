#pragma once

#include "Events.h"
#include "Components.h"

namespace gama{

    class PhysicsEngine: public EventHandler{
    public:
        explicit PhysicsEngine(Timeline* anchor): m_PhysicsTimeline(anchor){};
        void Initialize();
        void Simulate();
        void OnEvent(Event& event) override;
        void Shutdown();
        ~PhysicsEngine(){m_PhysicsBodies.clear();};
    private:
        constexpr const static float GRAVITY = 0.5;
        constexpr const static float FRICTION = 0.99;
        constexpr const static float AIR_RESISTANCE = 0.1;
        constexpr const static float IMPULSE_HORIZONTAL = 1;
        constexpr const static float IMPULSE_VERTICAL = 1.5;

        std::unordered_map<long, PhysicsBody*> m_PhysicsBodies;
        std::unordered_map<long, PhysicsBody*> m_Saved;
        Timeline* m_PhysicsTimeline;
        int64_t m_LastSimulationTime;
    };
}