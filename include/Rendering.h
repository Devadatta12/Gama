#pragma once

#include "iostream"
#include "unordered_map"
#include "map"
#include "vector"
#include "deque"
#include "Components.h"
#include "Events.h"

namespace gama {

    class RenderingEngine: public EventHandler{
    public:
        explicit RenderingEngine(): m_RenderingTimeline(new Timeline(nullptr, 17)), m_ResizeMode(false) {};
        void Initialize(std::string game);
        bool PollWindow();
        void Render();
        void OnEvent(Event& event) override;
        void Shutdown();
        ~RenderingEngine(){delete m_Window, delete m_Camera;};
    private:
        std::map<long, Mesh*> m_RenderMeshes;
        std::map<long, sf::Vector2f> m_Saved;
        sf::Vector2f m_CamSaved;
        std::deque<sf::Vector2f*> m_SpawnLocations;
        std::vector<long> m_CameraUUIDs;
        Timeline* m_RenderingTimeline;
        sf::RenderWindow* m_Window = nullptr;
        sf::View* m_Camera = nullptr;
        long m_LastRenderedTime = 0;
        bool m_ResizeMode;
    };

}