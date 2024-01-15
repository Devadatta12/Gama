#include "Collisions.h"

namespace gama {

    void CollisionSolver::Resolve(CollisionInfo collision) {
        EventManager::collided_type = collision.CollidedType;
        EventManager::collided_uuid = collision.CollidedUUID;
        switch (collision.CollidedType) {
            case FIXED_PLATFORM:
            {
                Event pEvent(Event::EventRigidCollision, 0);
                pEvent.priority = 0;
                pEvent.physicsEvent.characterUUID = collision.CharacterUUID;
                pEvent.physicsEvent.collidedUUID = collision.CollidedUUID;
                pEvent.physicsEvent.collisionResultantX = collision.CollisionX;
                pEvent.physicsEvent.collisionResultantY = collision.CollisionY;
                EventManager::GetInstance()->Raise(pEvent);
                break;
            }
            case COLLECTIBLE_ITEM:
            {
                Event scoringEvent(Event::EventScoring, 0);
                scoringEvent.scoringEvent.uuid = collision.CharacterUUID;
                EventManager::GetInstance()->Execute(scoringEvent);
                break;
            }
            case MOVING_PLATFORM:
            {
                Event scoringEvent(Event::EventScoring, 0);
                scoringEvent.scoringEvent.uuid = collision.CharacterUUID;
                EventManager::GetInstance()->Execute(scoringEvent);
                break;
            }
            case DEATH_ZONE:
            {
                Event scoring(Event::EventDeath, 0);
                scoring.priority = 0;
                scoring.scoringEvent.uuid = collision.CharacterUUID;
                EventManager::GetInstance()->Execute(scoring);
                break;
            }
            case SIDE_BOUNDARY:
            {
                Event renderEvent(Event::EventCameraFollow, 0);
                renderEvent.priority = 0;
                renderEvent.renderingEvent.otherUUID = collision.CollidedUUID;
                renderEvent.renderingEvent.mainUUID = collision.CharacterUUID;
                EventManager::GetInstance()->Raise(renderEvent);

                //TODO: DISPATCH EVENT TO THE NETWORK / RENDERING SYSTEM.
                break;
            }
        }
    }
}