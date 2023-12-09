#pragma once

#include "SFML/Graphics.hpp"
#include "Entities.h"
#include "Input.h"
#include "iostream"
#include "unordered_map"
#include "deque"
#include "Events.h"

namespace gama {

    class ObjectRuntimeSpecs{
    public:
        std::deque<sf::Vector2f> spawnObjects = {sf::Vector2f(120, 350), sf::Vector2f(80, 350),
                                                  sf::Vector2f(40, 350), sf::Vector2f(700, 350)};
    };

    class World: public EventHandler{
    public:
        explicit World(Timeline* anchor, bool isServer, int peerNumber): m_Anchor(anchor),
                                                                      m_Mutex(new std::mutex()), SEQ(0), m_IsServer(isServer), m_Peer(peerNumber){};
        void Initialize();
        void Update();
        void OnEvent(Event& event) override;
        std::string Serialize();
        void Shutdown();
        ~World() {m_Anchor = nullptr, delete m_Mutex;};
    private:
        ObjectRuntimeSpecs m_Specs;
        std::unordered_map<long, Entity*> m_Entities;
        Timeline* m_Anchor;
        std::mutex* m_Mutex;
        int64_t m_LastUpdateTime = 0;
        long SEQ;
        int m_Peer;
        bool m_IsServer;
    };

    class ScoringSystem: public EventHandler{
   public:
       ScoringSystem() = default;
       void Initialize(Timeline* anchor);
       void OnEvent(Event& event) override;
       void Shutdown();
       ~ScoringSystem() = default;
   private:
        Timeline* m_ScoringTimeline = nullptr;
       std::deque<sf::Vector2f*> m_SpawnLocations;
   };
}
