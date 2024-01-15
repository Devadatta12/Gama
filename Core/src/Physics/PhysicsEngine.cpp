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
            float currYVel = physicsBody->m_Velocity->y;
            if (physicsBody->m_Gravity && physicsBody->m_NotOnSurface){
                physicsBody->m_Velocity->y += GRAVITY;
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
            } else if(!physicsBody->m_Animated && !physicsBody->m_Stationary && !physicsBody->m_Gravity){
                if (currXVel < 0){
                    physicsBody->m_Velocity->x += (-currXVel < FRICTION) ? -currXVel : FRICTION;
                } else if (currXVel > 0) {
                    physicsBody->m_Velocity->x -= (currXVel < FRICTION) ? currXVel : FRICTION;
                }
                if (currYVel < 0){
                    physicsBody->m_Velocity->y += (-currYVel < FRICTION) ? -currYVel : FRICTION;
                } else if (currYVel > 0) {
                    physicsBody->m_Velocity->y -= (currYVel < FRICTION) ? currYVel : FRICTION;
                }
            }
        }
    }

    void PhysicsEngine::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventRigidCollision:
            {
                long characterUUID = event.physicsEvent.characterUUID;
                long collidedUUID = event.physicsEvent.collidedUUID;
                PhysicsBody* character = m_PhysicsBodies.find(characterUUID)->second;
                PhysicsBody* collided = m_PhysicsBodies.find(collidedUUID)->second;
                if (character->m_Gravity){
                    if (event.physicsEvent.collisionResultantY == -1){
                        character->m_Velocity->y = 0;
                        character->m_NotOnSurface = false;
                    }
                    character->m_Velocity->x = 0;
                } else{
                    auto characterMesh = character->m_Mesh;
                    auto collidedMesh = collided->m_Mesh;
                    float actorPosX = characterMesh->GetPosition().x;
                    float actorPosY = characterMesh->GetPosition().y;
                    if (character->m_UnitMovementX == 1 &&
                            (collidedMesh->GetPosition().x > actorPosX)){
                        actorPosX = collidedMesh->GetBoundingBox().left - characterMesh->GetSize().x - 1;
                        character->m_Velocity->x = 0;
                    } else if (character->m_UnitMovementX == -1 &&
                                ((collidedMesh->GetPosition().x + collidedMesh->GetSize().x) <
                                (actorPosX+characterMesh->GetSize().x))){
                        actorPosX = collidedMesh->GetBoundingBox().left +
                                    collidedMesh->GetBoundingBox().width + 1;
                        character->m_Velocity->x = 0;
                    }
                    if (character->m_UnitMovementY == 1 &&
                            (actorPosY < collidedMesh->GetBoundingBox().top)){
                        std::cout<<"Collision: "<< collidedMesh->GetPosition().x<< collidedMesh->GetPosition().y<<std::endl;
                        actorPosY = collidedMesh->GetBoundingBox().top - characterMesh->GetSize().y - 1;
                        character->m_Velocity->y = 0;
                    } else if (character->m_UnitMovementY == -1 &&
                               (actorPosY + characterMesh->GetBoundingBox().height >
                               (collidedMesh->GetBoundingBox().top + collidedMesh->GetBoundingBox().height))){
                        actorPosY = collidedMesh->GetBoundingBox().top + collidedMesh->GetBoundingBox().height+1;
                        character->m_Velocity->y = 0;
                    }

                    sf::Vector2f resolvedLocation = sf::Vector2f(actorPosX, actorPosY);
                    characterMesh->Place(Mesh::ABSOLUTE, resolvedLocation);
                }
                break;
            }
            case Event::EventMovement:
            {
                long characterUUID = event.physicsEvent.characterUUID;
                PhysicsBody* character = m_PhysicsBodies.find(characterUUID)->second;
                if (character->m_Gravity){
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
                } else if (!character->m_Animated && !character->m_Stationary && !character->m_Gravity) {
                    character->m_Velocity->x += IMPULSE_HORIZONTAL * event.physicsEvent.impulseX;
                    character->m_Velocity->y += IMPULSE_VERTICAL * event.physicsEvent.impulseY;
                    if (character->m_Velocity->x < 0)
                        character->m_UnitMovementX = -1;
                    else if(character->m_Velocity->x > 0)
                        character->m_UnitMovementX = 1;
                    else
                        character->m_UnitMovementX = 0;

                    if (character->m_Velocity->y < 0)
                        character->m_UnitMovementY = -1;
                    else if(character->m_Velocity->y > 0)
                        character->m_UnitMovementY = 1;
                    else
                        character->m_UnitMovementY = 0;
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