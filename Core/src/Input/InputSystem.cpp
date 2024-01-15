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
            FireAction fireAction = input.GetFireAction();
            WindowAction wAction = input.GetWindowAction();
            TimeAction timeAction = input.GetTimeAction();
            ControlAction controlAction = input.GetControlAction();


            int64_t currTime = m_Movement->getTime();
            int64_t delta = currTime - m_LastMovementTime;

            if (delta >= 1){
                if (controlAction.clockwise ^ controlAction.anticlockwise){
                    EventManager::curr_uuid = m_CharacterUUID;
                    EventManager::input_type = controlAction.clockwise ? 1 : 2;
                    r_ScriptManager->runOne("Input", false,"object_context");
                }

                if (m_ChordPlaying && !fireAction.hasFired){
                    m_ChordStarted = false;
                }

                if (m_ChordPlaying && !fireAction.hasFired && !motion.hasMoved){
                    m_ChordPlaying = false;
                }
                m_Chord++;
                if (m_Chord > 0 && m_Chord < 240 && motion.hasMoved && fireAction.hasFired && !m_ChordPlaying){
                    m_ChordPlaying = true;
                    if (r_ScriptManager != nullptr){
                        EventManager::curr_uuid = m_CharacterUUID;
                        EventManager::input_type = 0;
                        r_ScriptManager->runOne("Input", false);
                    } else{
                        std::cout<<"No scripting support"<<std::endl;
                    }
                    // ScriptManager.runOnce(thisGame.input);
                    // SCRIPTS WILL DECIDE WHETHER TO CHANGE TEXTURE TOGGLE_RENDERING,
                    // OR WHETHER TO HEAL(AS in the first game) HEAL.

                    // If motion and in under a second 'S' button is pressed then fire a bullet in that direction.
                    Event projectile(Event::EventCreateProjectile, 0);
                    auto impulseX = static_cast<float>(motion.right - motion.left);
                    auto impulseY = static_cast<float>(motion.down - motion.up);
                    projectile.inputEvent.dir_x = impulseX;
                    projectile.inputEvent.dir_y = impulseY;
                    projectile.inputEvent.characterUUID = m_CharacterUUID;
                    EventManager::GetInstance()->Execute(projectile);
                    //m_LastMovementTime = currTime;
                }
                else if (motion.hasMoved && !m_ChordPlaying){
                    // If motion and in under a second 'S' button is pressed then fire a bullet in that direction.
                    Event movement(Event::EventMovement, 0);
                    movement.physicsEvent.impulseX = static_cast<float>(motion.right - motion.left);
                    movement.physicsEvent.impulseY = static_cast<float>(motion.down - motion.up);
                    movement.physicsEvent.characterUUID = m_CharacterUUID;
                    EventManager::GetInstance()->Execute(movement);
                    //m_LastMovementTime = currTime;
                } else if (fireAction.hasFired && !motion.hasMoved && !m_ChordPlaying){
                    EventManager::curr_uuid = m_CharacterUUID;
                    r_ScriptManager->runOne("Editing", true, "object_context");
                }

                if (m_Chord > 240){
                    m_Chord = 0;
                }
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