#pragma once

#include "SFML/Graphics.hpp"
#include "iostream"
#include "Events.h"
#include "ScriptManager.h"

namespace gama {

#define UP

#define INPUT_KEYBOARD_UP   0x0001  // MOVE IN UPWARD DIRECTION.
#define INPUT_KEYBOARD_DOWN 0x0002  // MOVE IN DOWNWARD DIRECTION.
#define INPUT_KEYBOARD_LEFT 0x0004  // MOVE IN LEFT DIRECTION.
#define INPUT_KEYBOARD_RIGHT 0X0008 // MOVE IN RIGHT DIRECTION.
#define INPUT_KEYBOARD_W 0X0010     // CHANGE WINDOW SCALING MODE.
#define INPUT_KEYBOARD_R 0x0020     // INCREASE TIME SPEED.
#define INPUT_KEYBOARD_E 0x0040     // DECREASE TIME SPEED.
#define INPUT_KEYBOARD_P 0x0080     // PAUSE/PLAY.
#define INPUT_KEYBOARD_Q 0x0100     // REPLAY.
#define INPUT_KEYBOARD_S 0x0200     // REPLAY.
#define INPUT_KEYBOARD_A 0x0400     // A.
#define INPUT_KEYBOARD_D 0x0800     // D.

#define TIME_FACTOR 5

    class Motion {
    public:
        Motion(int up, int down, int left, int right):
                up(up), down(down), left(left), right(right),
                hasMoved(up | down | left | right){};
        bool hasMoved;
        int up;
        int down;
        int right;
        int left;
    };

    class TimeAction{
    public:
        TimeAction(bool pause, short speed): pause(pause), speed(speed),
                                             hasChanged(pause | speed){};
        bool hasChanged;
        bool pause;
        short speed;
    };

    class WindowAction{
    public:
        explicit WindowAction(bool mode, bool replay): hasToggled(mode), recordingToggle(replay) {};
        bool hasToggled;
        bool recordingToggle;
    };

    class FireAction{
    public:
        explicit FireAction(bool hasFired): hasFired(hasFired) {};
        bool hasFired;
    };

    class ControlAction{
    public:
        explicit ControlAction(bool clockwise, bool anticlockwise): clockwise(clockwise), anticlockwise(anticlockwise) {};
        bool clockwise;
        bool anticlockwise;
    };

    class KeyInput {
    public:
        explicit KeyInput(short bitVector): m_BitVector(bitVector) {};
        Motion GetMotion() const;
        TimeAction GetTimeAction() const;
        WindowAction GetWindowAction() const;
        FireAction GetFireAction() const;
        ControlAction GetControlAction() const;

    private:
        short m_BitVector;
    };

    KeyInput PollKeyboard();

    class InputSystem: public EventHandler{
    public:
        explicit InputSystem(Timeline* anchor): m_Movement(new Timeline(anchor, 1)),
            m_Toggle(new Timeline(nullptr, 2000)){};
        void Initialize();
        void OnEvent(Event& event) override;
        void AddScripting(ScriptManager* sm){r_ScriptManager = sm;};
        void Poll();
        void Shutdown();
        long GetCharacterUUID(){return m_CharacterUUID;};
    private:
        ScriptManager* r_ScriptManager;
        Timeline* m_Movement;
        Timeline* m_Toggle;
        int64_t m_LastMovementTime = 0;
        int64_t m_LastToggleTime = 0;
        long m_CharacterUUID = -1;
        int64_t m_Chord = 0;
        bool m_ChordPlaying = false;
        bool m_ChordStarted = false;
        bool m_JustFired = false;
        bool m_StillFiring = false;
        bool m_NoFire = true;
        bool m_JustMoved = false;
        bool m_StillMoving = false;
        bool m_StoppedMoving = true;
        volatile bool m_Enabled = false;
    };
}