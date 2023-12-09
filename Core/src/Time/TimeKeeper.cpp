#include "TimeKeeper.h"

namespace gama {

    void TimeKeeper::Initialize() {
        EventManager::GetInstance()->Register(this, TIME_EVENTS);
    }

    void TimeKeeper::Keep(int key, Timeline *timeline) {
        m_Timelines.insert({key, timeline});
    }

    void TimeKeeper::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventTimeSpeed:
            {
                Timeline* timeline = m_Timelines.find(event.timeEvent.key)->second;
                timeline->changeTic(event.timeEvent.speed);
                Event timeEvent(Event::EventUpdateTime, 0);
                EventManager::GetInstance()->Execute(timeEvent);
                break;
            }
            case Event::EventPausePlayToggle:
            {
                Timeline* timeline = m_Timelines.find(event.timeEvent.key)->second;
                if (timeline->isPaused()){
                    timeline->unpause();
                } else{
                    timeline->pause();
                }
                Event timeEvent(Event::EventUpdateTime, 0);
                EventManager::GetInstance()->Execute(timeEvent);
                break;
            }
            default:
                break;
        }
    }

    void TimeKeeper::Shutdown() {

    }
}