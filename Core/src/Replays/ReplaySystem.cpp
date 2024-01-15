#include "Replays.h"
#include "iostream"

namespace gama{

    void ReplaySystem::Initialize() {
        EventManager::GetInstance()->Register(this, REPLAY_EVENTS);
    }

    void ReplaySystem::OnEvent(Event &event) {
        if (m_IsRecording && event.type != Event::EventRecord){
            auto recorded = new Event(event);
            if (event.type == Event::EventSyncWorld)
            {
                recorded->worldEvent.message = new std::string(*event.worldEvent.message);
            }
            m_RecordedEvents.push_back(recorded);
        }
        switch (event.type) {
            case Event::EventRecord:
            {
                if (m_IsRecording){
                    Timeline temp(nullptr, 8);
                    int64_t m_LastTime = temp.getTime();
                    Event startReplay(Event::EventStartReplay, 0);
                    EventManager::GetInstance()->Execute(startReplay);
                    int64_t currTime = temp.getTime();
                    int64_t delta = 0;
                    for (auto record: m_RecordedEvents){
                        //delta = currTime - m_LastTime;
                        while (delta < 1000){
                            delta++;
                        }
                        EventManager::GetInstance()->Execute(*record);
                    }
                    m_RecordedEvents.clear();
                    Event endReplay(Event::EventEndReplay, 0);
                    EventManager::GetInstance()->Execute(endReplay);
                    m_IsRecording = false;
                } else {
                    Event startRecording(Event::EventStartRecording, 0);
                    EventManager::GetInstance()->Execute(startRecording);
                    m_IsRecording = true;
                }
                break;
            }
            default:
                break;
        }
    }

    void ReplaySystem::Shutdown() {

    }
}