#include "Events.h"
#include "iostream"

namespace gama {

    void EventManager::Raise(const v8::FunctionCallbackInfo<v8::Value> &args) {
        v8::String::Utf8Value eventStr(args.GetIsolate(), args[0]);
        int eventId = std::stoi(*eventStr);
        if (Event::EventDeath == eventId){
            Event scriptEvent((Event::EventType)eventId, 0);
            scriptEvent.scoringEvent.uuid = curr_uuid;
            s_EventMgr->Execute(scriptEvent);
        } else{
            Event scriptEvent((Event::EventType)eventId, 0);
            s_EventMgr->Execute(scriptEvent);
        }
    }

    EventManager* EventManager::s_EventMgr = nullptr;
    bool onceEvent = true;
    long EventManager::curr_uuid = -1;
    long EventManager::collided_uuid = -1;
    long EventManager::collided_type = -1;
    long EventManager::input_type = -1;

    EventManager* EventManager::GetInstance() {
        if (s_EventMgr == nullptr){
            s_EventMgr = new EventManager();
        }
        return s_EventMgr;
    }

    void EventManager::Initialize(Timeline *anchor) {
        m_GlobalTimeline = new Timeline(anchor, 1);
        m_LastDispatchTime = m_GlobalTimeline->getTime();
    }

    void EventManager::Register(EventHandler *handler, const std::vector<Event::EventType>& events) {
        for (auto event: events) {
            if (m_EventHandlers.find(event) == m_EventHandlers.end()){
                m_EventHandlers.insert({event, {handler}});
            } else{
                auto handlers = m_EventHandlers.find(event)->second;
                handlers.push_back(handler);
                m_EventHandlers.erase(event);
                m_EventHandlers.insert({event, handlers});
            }
        }
    }

    void EventManager::Dispatch() {
        if (m_GlobalTimeline != nullptr){
            int64_t currTime = m_GlobalTimeline->getTime();
            int64_t delta = currTime - m_LastDispatchTime;
            if (delta < 1){
                return;
            }
            m_LastDispatchTime = currTime;
            if (m_EventQueue.empty()){
                return;
            }
            auto event = m_EventQueue.top();
            while (!m_EventQueue.empty() && event.priority <= currTime){

                if (m_EventHandlers.find(event.type) != m_EventHandlers.end()){
                    auto handlers = m_EventHandlers.find(event.type)->second;
                    for (auto handler: handlers) {
                        handler->OnEvent(event);
                    }
                }
                m_EventQueue.pop();
                event = m_EventQueue.top();
            }
        }
    }

    void EventManager::Execute(Event &event) {
        if (m_EventHandlers.find(event.type) != m_EventHandlers.end()){
            auto handlers = m_EventHandlers.find(event.type)->second;
            for (auto handler: handlers) {
                handler->OnEvent(event);
            }
        }
    }

    void EventManager::Raise(Event event) {
        m_EventQueue.push(event);
    }

}