#include "Collisions.h"
#include "Events.h"

namespace gama{

    bool isCollision(CollisionMesh* mesh1, CollisionMesh* mesh2){
        return mesh1->GetBoundingBox().intersects(mesh2->GetBoundingBox());
    }

    // Only invoked when collision is detected.
    CollisionInfo extractCollisionInfo(CollisionMesh* actor, CollisionMesh* collided){
        sf::FloatRect actorBox = actor->GetBoundingBox();
        sf::FloatRect collidedBox = collided->GetBoundingBox();
        CollisionInfo collision;
        collision.CollidedType = collided->GetType();
        // Actor to the left hand side of Collidable.
        if ((actorBox.left + actorBox.width) <= collidedBox.left)
            collision.CollisionX -= 1, collision.CollisionY = 0;
        // Actor to the right hand side of Collidable.
        if ((collidedBox.left + collidedBox.width) <= actorBox.left)
            collision.CollisionX += 1, collision.CollisionY = 0;
        // Actor on the top side of Collidable.
        if ((actorBox.top + actorBox.height) >= collidedBox.top && actorBox.top < collidedBox.top)
            collision.CollisionY = -1;
        // Actor on the bottom side of Collidable.
        if ((collidedBox.top < actorBox.top) &&
        ((collidedBox.top+collidedBox.height) == actorBox.top) &&
                ((actorBox.left+actorBox.width)>=collidedBox.left) &&
                (actorBox.left <=(collidedBox.left+collidedBox.width)))
            collision.CollisionY = +1;

        if (collision.CollisionY == 1)
            std::cout<<"Collision: "<<collision.CollisionY<<std::endl;
        return collision;
    }

    void CollisionSystem::Initialize() {
        EventManager::GetInstance()->Register(this, COLLISION_EVENTS);
        m_LastDetectionTime = m_CollisionTimeline->getTime();
    }

    void CollisionSystem::Detect() {
        int64_t currTime = m_CollisionTimeline->getTime();
        int64_t delta = currTime - m_LastDetectionTime;
        if (delta < 1){
            return;
        }
        m_LastDetectionTime = currTime;
        for (auto character: m_Actors) {
            for (auto collidable: m_Collidables) {
                if (isCollision(character.second, collidable.second)){
                    CollisionInfo collision = extractCollisionInfo(character.second, collidable.second);
                    collision.CharacterUUID = character.first;
                    collision.CollidedUUID = collidable.first;
                    m_Solver->Resolve(collision);
                }
            }
        }
    }

    void CollisionSystem::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventAddCollision:
            {
                CollisionMesh* mesh = event.collisionEvent.collisionMesh;
                long uuid = event.collisionEvent.uuid;
                (event.collisionEvent.isActor)?(m_Actors.insert({uuid, mesh})):
                                                (m_Collidables.insert({uuid, mesh}));
                return;
            }
            case Event::EventUpdateTime:
            {
                m_LastDetectionTime = m_CollisionTimeline->getTime();
            }
            default:
                return;
        }
    }

    void CollisionSystem::Shutdown() {

    }

}