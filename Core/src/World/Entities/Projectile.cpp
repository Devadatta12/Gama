#include "Entities.h"
#include "Events.h"

namespace gama{

    Entity *Projectile::Construct(Timeline *anchor, std::string &serialized) {
        bool isLocal = false;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float directionX = std::stof(tokens[4]);
        float directionY = std::stof(tokens[5]);

        Entity* projectile = new Projectile(uuid, isLocal, anchor,
                                              new sf::Vector2f(posX, posY),
                                              new sf::Vector2f(directionX, directionY));
        return projectile;
    }

    std::string *Projectile::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        serialized += std::to_string(GetType())+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(m_Physics->m_Velocity->x)+"#";
        serialized += std::to_string(m_Physics->m_Velocity->y)+"+";
        return new std::string(serialized);
    }

    Projectile::Projectile(long uuid, bool isLocal, Timeline *anchor, sf::Vector2f *initPos, sf::Vector2f* velocity) :
            Entity(uuid, isLocal, anchor, PROJECTILE) {
        auto* sprite = new sf::Sprite();
        auto* texture = new sf::Texture();
        if (!texture->loadFromFile("./resources/astronaut.png"))
        {
            std::cout << "Error loading texture" << std::endl;
        }
        sprite->setTexture(*texture);
        sprite->setPosition(initPos->x, initPos->y);
        sprite->scale(0.1,0.1);
        m_VelocityX = velocity->x;
        m_VelocityY = velocity->y;

        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.sprite = sprite;
        m_Mesh = ComponentFactory::AddMesh(specs);  // RENDERING.

        specs.mesh = m_Mesh, specs.isStationary = false, specs.gravityEffect = false;
        specs.collisionType = PROJECTILE, specs.isActor = true;

//        m_Physics = ComponentFactory::AddPhysics(specs);    // PHYSICS.
//        m_Physics->m_Animated = true;
//        m_Physics->m_Velocity->x = 0.000003*velocity->x;
//        m_Physics->m_Velocity->y = 0.000003*velocity->y;
        m_Collision = ComponentFactory::AddCollision(specs);      // COLLISION.
    }

    void Projectile::Update() {
        int64_t currTime = m_Timeline->getTime();
        int64_t delta = currTime - m_LastTime;
        sf::Vector2f movement(m_VelocityX, m_VelocityY);
        std::cout<<"Moving"<<std::endl;
        m_Mesh->Place(Mesh::RELATIVE, movement);
        m_LastTime = currTime;
//        m_Physics->Simulate(delta);
    }

    void Projectile::OnEvent(float posX, float posY) {
        sf::Vector2f location(posX, posY);
        m_Mesh->Place(Mesh::ABSOLUTE, location);
    }

    void Projectile::Draw(sf::RenderWindow& window) {
        m_Mesh->Draw(window);
    }

    std::string Projectile::Sync() {
        std::string sync;
        sync += std::to_string(m_UUID)+"#";
        sync += std::to_string(m_Mesh->GetPosition().x)+"#";
        sync += std::to_string(m_Mesh->GetPosition().y)+"#";
        sync += std::to_string(m_Physics->m_Velocity->x)+"#";
        sync += std::to_string(m_Physics->m_Velocity->y)+"+";
        return sync;
    }

    void Projectile::Release() {
        ComponentFactory::RemoveMesh(m_UUID);
    }

}

