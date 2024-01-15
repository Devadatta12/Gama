#include "Components.h"
#include "iostream"

namespace gama{
    // Components
    void Mesh::Draw(sf::RenderWindow &window) {
        if (!m_Hidden){
            if (m_Sprite != nullptr){
                window.draw(*m_Sprite);
            } else {
                window.draw(*m_Shape);
            }
        }
    }

    void Mesh::Place(short positioning, sf::Vector2f &location) {
        if (m_Sprite != nullptr){
            (positioning==ABSOLUTE)?m_Sprite->setPosition(location):m_Sprite->move(location);
        } else {
            (positioning==ABSOLUTE)?m_Shape->setPosition(location):m_Shape->move(location);
        }
    }

    sf::Vector2f Mesh::GetPosition() {
        if (m_Sprite != nullptr){
            return m_Sprite->getPosition();
        } else {
            return m_Shape->getPosition();
        }
    }

    sf::Vector2f Mesh::GetSize() {
        if (m_Shape != nullptr){
            return m_Shape->getSize();
        }
        return {m_Sprite->getGlobalBounds().width, m_Sprite->getGlobalBounds().height};
    }

    sf::FloatRect Mesh::GetBoundingBox() {
        if (m_Sprite != nullptr){
            return m_Sprite->getGlobalBounds();
        } else {
            return m_Shape->getGlobalBounds();
        }
    }

    void PhysicsBody::Simulate(int64_t delta) const {
        if (!m_Stationary){
            m_Displacement->x = m_Velocity->x * static_cast<float>(delta);
            m_Displacement->y = m_Velocity->y * static_cast<float>(delta);
            m_Mesh->Place(Mesh::RELATIVE, *m_Displacement);
        }
    }


    void Animation::Animate(ScriptManager* sm, int64_t delta) {
        sm->runOne("Animation", true, "object_context");
//        float displacement = DEFAULT_VELOCITY* static_cast<float>(delta);
//        sf::Vector2f position = m_Mesh->GetPosition();
//        sf::Vector2f location;
//        if (m_AnimationType){
//            if (position.y >= 350 &&  m_Direction== 0){
//                location.x = 0, location.y = -displacement;
//                m_Direction = 1;
//            }
//            else if (position.y <= 180 && m_Direction == 1){
//                location.x = 0, location.y = displacement;
//                m_Direction = 0;
//            }
//            else if (m_Direction == 1)
//                location.x = 0, location.y = -displacement;
//            else
//                location.x = 0, location.y = displacement;
//            m_Mesh->Place(Mesh::RELATIVE, location);
//        } else {
//            if (position.x >= 380 &&  m_Direction== 0){
//                location.y = 0, location.x = -displacement;
//                m_Direction = 1;
//            }
//            else if (position.x <= 220 && m_Direction == 1){
//                location.y = 0, location.x = displacement;
//                m_Direction = 0;
//            }
//            else if (m_Direction == 1)
//                location.y = 0, location.x = -displacement;
//            else
//                location.y = 0, location.x = displacement;
//        }
//        m_Mesh->Place(Mesh::RELATIVE, location);
    }
}