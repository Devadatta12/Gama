#include "Input.h"
#include "TimeKeeper.h"

namespace gama{
    void InputSystem::Initialize() {
        EventManager::GetInstance()->Register(this, INPUT_EVENTS);
        m_LastMovementTime = m_Movement->getTime();
        m_LastToggleTime = m_Toggle->getTime();
    }

    void InputSystem::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventBindInput:
            {
                m_CharacterUUID = event.inputEvent.characterUUID;
                m_Enabled = true;
                break;
            }
            case Event::EventFocusGained:
            {
                m_Enabled = true;
                break;
            }
            case Event::EventFocusLost:
            {
                m_Enabled = false;
                break;
            }
            default:
                break;
        }
    }

    void InputSystem::Poll() {
        if (m_Enabled && m_CharacterUUID != -1){
            KeyInput input = PollKeyboard();
            Motion motion = input.GetMotion();
            WindowAction wAction = input.GetWindowAction();
            TimeAction timeAction = input.GetTimeAction();


            int64_t currTime = m_Movement->getTime();
            int64_t delta = currTime - m_LastMovementTime;
            //int64_t globalTime = m_Movement->getGlobalTime();

            if (motion.hasMoved && delta >= 1){
                Event movement(Event::EventMovement, 0);
                movement.physicsEvent.impulseX = static_cast<float>(motion.right - motion.left);
                movement.physicsEvent.impulseY = static_cast<float>(motion.down - motion.up);
                movement.physicsEvent.characterUUID = m_CharacterUUID;
                EventManager::GetInstance()->Execute(movement);
                m_LastMovementTime = currTime;
            } else if(delta >= 1){
                m_LastMovementTime = currTime;
            }

            int64_t currToggleTime = m_Toggle->getTime();
            int64_t toggleDelta = currToggleTime - m_LastToggleTime;

            if (timeAction.hasChanged && toggleDelta >= 1){
                if (timeAction.pause){
                    Event event(Event::EventPausePlayToggle, 0);
                    event.timeEvent.pauseToggled = true;
                    event.timeEvent.speed = 0;
                    event.timeEvent.key = TimeKeeper::WILDCARD;
                    EventManager::GetInstance()->Execute(event);
                    m_LastToggleTime = m_Toggle->getTime();
                    m_LastMovementTime = m_Movement->getTime();
                } else{
                    Event event(Event::EventTimeSpeed, 0);
                    event.timeEvent.speed = timeAction.speed;
                    event.timeEvent.pauseToggled = false;
                    event.timeEvent.key = TimeKeeper::WILDCARD;
                    EventManager::GetInstance()->Execute(event);
                    m_LastToggleTime = m_Toggle->getTime();
                    m_LastMovementTime = m_Movement->getTime();
                }
            }

            if (wAction.hasToggled && toggleDelta >= 1){
                m_LastToggleTime = m_Toggle->getTime();
                Event windowModeChange(Event::EventWindowMode, m_Movement->getGlobalTime()+15);
                windowModeChange.renderingEvent.modeToggled = true;
                EventManager::GetInstance()->Raise(windowModeChange);
            }
            if (wAction.recordingToggle && toggleDelta >= 1){
                m_LastToggleTime = m_Toggle->getTime();
                Event recordingEvent(Event::EventRecord, m_Movement->getGlobalTime());
                EventManager::GetInstance()->Raise(recordingEvent);
            }
        }
    }

    void InputSystem::Shutdown() {
        m_Enabled = false;
    }
}