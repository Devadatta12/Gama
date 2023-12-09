#pragma once

#include "SFML/Graphics.hpp"
#include "iostream"
#include "Events.h"

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

    class KeyInput {
    public:
        explicit KeyInput(short bitVector): m_BitVector(bitVector) {};
        Motion GetMotion() const;
        TimeAction GetTimeAction() const;
        WindowAction GetWindowAction() const;

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
        void Poll();
        void Shutdown();
    private:
        Timeline* m_Movement;
        Timeline* m_Toggle;
        int64_t m_LastMovementTime = 0;
        int64_t m_LastToggleTime = 0;
        long m_CharacterUUID = -1;
        volatile bool m_Enabled = false;
    };
}