//
// Created by Devadatta Mandaogane on 02/10/23.
//

#include "Input.h"

namespace gama{


    KeyInput PollKeyboard(){
        short bitVector = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            bitVector |= INPUT_KEYBOARD_UP;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            bitVector |= INPUT_KEYBOARD_DOWN;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            bitVector |= INPUT_KEYBOARD_LEFT;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            bitVector |= INPUT_KEYBOARD_RIGHT;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            bitVector |= INPUT_KEYBOARD_W;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            bitVector |= INPUT_KEYBOARD_R;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            bitVector |= INPUT_KEYBOARD_E;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            bitVector |= INPUT_KEYBOARD_P;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            bitVector |= INPUT_KEYBOARD_Q;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            bitVector |= INPUT_KEYBOARD_S;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            bitVector |= INPUT_KEYBOARD_A;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            bitVector |= INPUT_KEYBOARD_D;
        }
        return KeyInput(bitVector);
    }

    Motion KeyInput::GetMotion() const {
        bool up = m_BitVector & INPUT_KEYBOARD_UP;
        bool down = m_BitVector & INPUT_KEYBOARD_DOWN;
        bool left = m_BitVector & INPUT_KEYBOARD_LEFT;
        bool right = m_BitVector & INPUT_KEYBOARD_RIGHT;
        return Motion(up, down, left, right);
    }

    TimeAction KeyInput::GetTimeAction() const {
        bool pause = m_BitVector & INPUT_KEYBOARD_P;
        bool increase = m_BitVector & INPUT_KEYBOARD_R;
        bool decrease = m_BitVector & INPUT_KEYBOARD_E;
        short speed = decrease * TIME_FACTOR - increase * TIME_FACTOR;
        return TimeAction(pause, speed);
    }

    WindowAction KeyInput::GetWindowAction() const {
        bool mode = m_BitVector & INPUT_KEYBOARD_W;
        bool replay = m_BitVector & INPUT_KEYBOARD_Q;
        return WindowAction(mode, replay);
    }

    FireAction KeyInput::GetFireAction() const {
        bool hasFired = m_BitVector & INPUT_KEYBOARD_S;
        return FireAction(hasFired);
    }

    ControlAction KeyInput::GetControlAction() const {
        bool anticlockwise = m_BitVector & INPUT_KEYBOARD_A;
        bool clockwise = m_BitVector & INPUT_KEYBOARD_D;
        return ControlAction(clockwise, anticlockwise);
    }
}
