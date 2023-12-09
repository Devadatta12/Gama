#pragma once
#include "Events.h"
#include "deque"

namespace gama {
    class ReplaySystem: public EventHandler{
    public:
        ReplaySystem():m_IsRecording(false){}
        void Initialize();
        void OnEvent(Event& event) override;
        void Shutdown();
    private:
        std::deque<Event*> m_RecordedEvents;
        bool m_IsRecording;
    };
}