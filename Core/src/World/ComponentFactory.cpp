#include "Events.h"
#include "Components.h"


namespace gama {

    Mesh* ComponentFactory::AddMesh(ComponentSpecs& specs) {
        Mesh* mesh = nullptr;
        if (specs.sprite != nullptr)
            mesh = new Mesh(specs.sprite);
        else
            mesh = new Mesh(specs.shape, specs.isHidden);
        Event addRenderMesh(Event::EventAddRendering, 0);
        addRenderMesh.renderingEvent.mesh = mesh;
        addRenderMesh.renderingEvent.mainUUID = specs.uuid;
        EventManager::GetInstance()->Execute(addRenderMesh);
        return mesh;
    }

    void ComponentFactory::RemoveMesh(long uuid) {
        Event addRenderMesh(Event::EventRemoveRendering, 0);
        addRenderMesh.renderingEvent.mainUUID = uuid;
        EventManager::GetInstance()->Execute(addRenderMesh);
    }

    PhysicsBody *ComponentFactory::AddPhysics(ComponentSpecs& specs) {
        auto* physicsBody = new PhysicsBody(specs.mesh, specs.isStationary, specs.gravityEffect);
        Event addPhysics(Event::EventAddPhysics, 0);
        addPhysics.physicsEvent.physicsBody = physicsBody;
        addPhysics.physicsEvent.characterUUID = specs.uuid;
        EventManager::GetInstance()->Execute(addPhysics);
        return physicsBody;
    }

    Animation *ComponentFactory::AddAnimation(ComponentSpecs& specs) {
        auto* animation = new Animation(specs.mesh, specs.animationType);
        return animation;
    }

    CollisionMesh *ComponentFactory::AddCollision(ComponentSpecs& specs) {
        CollisionMesh* mesh = nullptr;
        if (specs.sprite != nullptr)
            mesh = new CollisionMesh(specs.sprite, specs.collisionType);
        else
            mesh = new CollisionMesh(specs.shape, specs.collisionType);

        Event addCollision(Event::EventAddCollision, 0);
        addCollision.collisionEvent.uuid = specs.uuid;
        addCollision.collisionEvent.collisionMesh = mesh;
        addCollision.collisionEvent.isActor = specs.isActor;
        EventManager::GetInstance()->Execute(addCollision);
        return mesh;
    }

    Camera *ComponentFactory::AddCamera(ComponentSpecs& specs) {
        auto* camera = new Camera(specs.uuid);
        Event addCamera(Event::EventPinCamera, 0);
        addCamera.renderingEvent.mainUUID = specs.uuid;
        EventManager::GetInstance()->Execute(addCamera);
        return camera;
    }

    void ComponentFactory::AddSpawnPoint(ComponentSpecs &specs) {
        Event addSpawnPoint(Event::EventAddSpawn, 0);
        addSpawnPoint.scoringEvent.spawnPointX = specs.spawnX;
        addSpawnPoint.scoringEvent.spawnPointY = specs.spawnY;
        EventManager::GetInstance()->Execute(addSpawnPoint);
    }


}
