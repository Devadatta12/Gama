#pragma once

#include "SFML/Graphics.hpp"
#include "Entities.h"
#include "Input.h"
#include "iostream"
#include "unordered_map"
#include "deque"
#include "Events.h"
#include "ScriptManager.h"

namespace gama {

    class ObjectRuntimeSpecs{
    public:
        std::deque<sf::Vector2f> spawnObjects = {sf::Vector2f(120, 350), sf::Vector2f(80, 350),
                                                  sf::Vector2f(40, 350), sf::Vector2f(700, 350)};
        std::deque<sf::Vector2f> spawnObjects2 = {sf::Vector2f(30, 10), sf::Vector2f(740, 10),
                                                 sf::Vector2f(30, 540), sf::Vector2f(740, 540)};
        std::deque<sf::Vector2f> spawnObjects3 = {sf::Vector2f(34, 0), sf::Vector2f(56, 350),
                                                 sf::Vector2f(82, 350), sf::Vector2f(108, 350)};
    };

    class World: public EventHandler{
    public:
        static void GetCalleeUUID(const v8::FunctionCallbackInfo<v8::Value>& args);
        explicit World(Timeline* anchor, bool isServer, int peerNumber, const std::string& game): m_Anchor(anchor),
                                                                      m_Mutex(new std::mutex()), SEQ(0), m_IsServer(isServer),
                                                                      m_Peer(peerNumber), m_GameName(game){};
        void Initialize();
        void Update();
        void OnEvent(Event& event) override;
        void Bind(v8::Isolate* isolate, v8::Local <v8::Context>& object_context);
        std::string Serialize();
        void AddScripting(ScriptManager* sm){
            r_ScriptManager = sm;
            for (auto entity: m_Entities) {
                if (entity.second->IsLocal()){
                    entity.second->AddScripting(r_ScriptManager);
                }
            }
        };
        void Shutdown();
        ~World() {m_Anchor = nullptr, delete m_Mutex;};
        long m_CharacterUUID;
    private:
        void game1();
        void game2();
        void game3();
        std::string m_GameName;
        ObjectRuntimeSpecs m_Specs;
        std::unordered_map<long, Entity*> m_Entities;
        Timeline* m_Anchor;
        ScriptManager* r_ScriptManager;
        std::mutex* m_Mutex;
        int64_t m_LastUpdateTime = 0;
        long SEQ;
        long PROJECTILES = 999999;
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
        void AddScripting(ScriptManager* sm){r_ScriptManager = sm;};
   private:
        Timeline* m_ScoringTimeline = nullptr;
        ScriptManager* r_ScriptManager;
       std::deque<sf::Vector2f*> m_SpawnLocations;
       std::unordered_map<int, int> m_Collected;
   };
}
