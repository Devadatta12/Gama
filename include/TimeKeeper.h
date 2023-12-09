#pragma once

#include "Timelines.h"
#include "Events.h"

namespace gama{

    class TimeKeeper: public EventHandler{
    public:
        constexpr const static int WILDCARD = 0;
        void Initialize();
        void Keep(int key, Timeline* timeline);
        void OnEvent(Event& event) override;
        void Shutdown();
    private:
        std::unordered_map<int, Timeline*> m_Timelines;
    };

}