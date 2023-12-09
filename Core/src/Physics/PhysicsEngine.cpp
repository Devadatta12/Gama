#include "Physics.h"
#include "iostream"

namespace gama {
    void PhysicsEngine::Initialize() {
        EventManager::GetInstance()->Register(this, PHYSICS_EVENTS);
        m_LastSimulationTime = m_PhysicsTimeline->getTime();
    }

    void PhysicsEngine::Simulate() {
        int64_t currTime = m_PhysicsTimeline->getTime();
        int64_t delta = currTime - m_LastSimulationTime;
        if (delta < 1){
            return;
        }
        m_LastSimulationTime = currTime;
        for (auto pIter: m_PhysicsBodies) {
            PhysicsBody* physicsBody = pIter.second;
            float currXVel = physicsBody->m_Velocity->x;
            if (physicsBody->m_Gravity && physicsBody->m_NotOnSurface){
                physicsBody->m_Velocity->y += GRAVITY;
            }
            if (!physicsBody->m_Animated && !physicsBody->m_Stationary && !physicsBody->m_NotOnSurface){
                if (currXVel < 0){
                    physicsBody->m_Velocity->x += (-currXVel < FRICTION) ? -currXVel : FRICTION;
                } else if (currXVel > 0) {
                    physicsBody->m_Velocity->x -= (currXVel < FRICTION) ? currXVel : FRICTION;
                }
            } else if (!physicsBody->m_Animated && !physicsBody->m_Stationary && physicsBody->m_NotOnSurface){
                if (currXVel < 0){
                    physicsBody->m_Velocity->x += (-currXVel < AIR_RESISTANCE) ? -currXVel : AIR_RESISTANCE;
                } else if (currXVel > 0) {
                    physicsBody->m_Velocity->x -= (currXVel < AIR_RESISTANCE) ? currXVel : AIR_RESISTANCE;
                }
            }
        }
    }

    void PhysicsEngine::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventRigidCollision:
            {
                long characterUUID = event.physicsEvent.characterUUID;
                PhysicsBody* character = m_PhysicsBodies.find(characterUUID)->second;
                if (event.physicsEvent.collisionResultantY == -1){
                    character->m_Velocity->y = 0;
                    character->m_NotOnSurface = false;
                }
                character->m_Velocity->x = 0;
                break;
            }
            case Event::EventMovement:
            {
                long characterUUID = event.physicsEvent.characterUUID;
                PhysicsBody* character = m_PhysicsBodies.find(characterUUID)->second;
                if (!character->m_NotOnSurface && event.physicsEvent.impulseY < 0){
                    character->m_NotOnSurface = true;
                }
                if (character->m_NotOnSurface){
                    character->m_Velocity->x += IMPULSE_HORIZONTAL * event.physicsEvent.impulseX;
                } else{
                    character->m_Velocity->x += IMPULSE_HORIZONTAL * event.physicsEvent.impulseX;
                }
                if (event.physicsEvent.impulseY < 0){
                    character->m_Velocity->y += IMPULSE_VERTICAL * event.physicsEvent.impulseY;
                }
                break;
            }
            case Event::EventAddPhysics:
            {
                PhysicsBody* physicsBody = event.physicsEvent.physicsBody;
                long characterUUID = event.physicsEvent.characterUUID;
                m_PhysicsBodies.insert({characterUUID, physicsBody});
                break;
            }
            case Event::EventResetPhysics:
            {
                long characterUUID = event.physicsEvent.characterUUID;
                PhysicsBody* character = m_PhysicsBodies.find(characterUUID)->second;
                character->m_Velocity->x = 0, character->m_Velocity->y = 0;
                character->m_NotOnSurface = true;
                break;
            }
            case Event::EventUpdateTime:
            {
                m_LastSimulationTime = m_PhysicsTimeline->getTime();
                break;
            }
            case Event::EventStartRecording:
            {
                for (auto physicsBody: m_PhysicsBodies) {
                    auto pCopy = new PhysicsBody(nullptr,
                                                         physicsBody.second->m_Stationary,
                                                         physicsBody.second->m_Gravity);
                    pCopy->m_Velocity = new sf::Vector2f(*physicsBody.second->m_Velocity);
                    pCopy->m_NotOnSurface = physicsBody.second->m_NotOnSurface;
                    pCopy->m_Animated = physicsBody.second->m_Animated;
                    pCopy->m_Displacement = new sf::Vector2f(*physicsBody.second->m_Displacement);
                    m_Saved.insert({physicsBody.first, pCopy});
                }
                break;
            }
            case Event::EventStartReplay:
            {
                for (auto physicsBody: m_PhysicsBodies) {
                    auto pCopy = m_Saved.find(physicsBody.first);
                    if (pCopy == m_Saved.end()){
                        continue;
                    }
                    physicsBody.second->m_Velocity->x = pCopy->second->m_Velocity->x;
                    physicsBody.second->m_Velocity->y = pCopy->second->m_Velocity->y;
                    physicsBody.second->m_NotOnSurface = pCopy->second->m_NotOnSurface;
                    physicsBody.second->m_Animated = pCopy->second->m_Animated;
                    physicsBody.second->m_Displacement->x = pCopy->second->m_Displacement->x;
                    physicsBody.second->m_Displacement->y = pCopy->second->m_Displacement->y;
                }
                m_Saved.clear();
                break;
            }
            default:
                break;
        }
    }

    void PhysicsEngine::Shutdown() {

    }
}