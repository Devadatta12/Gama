#include "Entities.h"
#include "Events.h"

namespace gama{

    Entity *FixedPlatform::Construct(Timeline *anchor, std::string &serialized) {
        bool isLocal = false;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float sizeX = std::stof(tokens[4]);
        float sizeY = std::stof(tokens[5]);
        int texture = std::stoi(tokens[6]);

        Entity* platform = new FixedPlatform(uuid, texture, isLocal, anchor,
                                              new sf::Vector2f(posX, posY),
                                              new sf::Vector2f(sizeX, sizeY) );
        return platform;
    }

    std::string *FixedPlatform::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        sf::Vector2f size = m_Mesh->GetSize();
        serialized += std::to_string(m_Type)+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(size.x)+"#";
        serialized += std::to_string(size.y)+"#";
        serialized += std::to_string(m_TextureType)+"+";
        return new std::string(serialized);
    }

    FixedPlatform::FixedPlatform(long uuid, int textureType, bool isLocal, Timeline* anchor, sf::Vector2f* position, sf::Vector2f* size):
            Entity(uuid, isLocal, anchor, FIXED_PLATFORM){
        auto* shape = new sf::RectangleShape(sf::Vector2f(size->x, size->y));
        auto* texture = new sf::Texture();
        m_TextureType = textureType;
        m_TextureId = textureType;
        std::string texturePath;
        texturePath = "./resources/"+std::to_string(textureType)+".png";
        if (!texture->loadFromFile(texturePath))
        {
                std::cout << "Error loading texture" << std::endl;
        }
        shape->setTexture(texture);
        shape->setPosition(position->x, position->y);

        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.shape = shape, specs.isHidden = false;
        m_Mesh = ComponentFactory::AddMesh(specs);  // RENDERING.

        specs.mesh = m_Mesh, specs.isStationary = true, specs.gravityEffect = false;
        specs.collisionType = FIXED_PLATFORM, specs.isActor = false;

        m_Physics = ComponentFactory::AddPhysics(specs);    // PHYSICS.
        m_Collision = ComponentFactory::AddCollision(specs);    // COLLISION.
    }

    void FixedPlatform::Update() {
        // DO NOTHING.
    }

    void FixedPlatform::Draw(sf::RenderWindow &window) {
        m_Mesh->Draw(window);
    }

    void FixedPlatform::OnEvent(float posX, float posY) {
    }

    std::string FixedPlatform::Sync() {
        return "";
    }

    Entity *MovingPlatform::Construct(gama::Timeline *anchor, std::string &serialized) {
        bool isLocal = false;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float sizeX = std::stof(tokens[4]);
        float sizeY = std::stof(tokens[5]);
        int animation = std::stoi(tokens[6]);
        int textureId = std::stoi(tokens[7]);
        bool animationType = (animation != 0);


        Entity* platform = new MovingPlatform(uuid, textureId, isLocal, anchor, animationType,
                                             new sf::Vector2f(posX, posY),
                                             new sf::Vector2f(sizeX, sizeY));
        return platform;
    }

    std::string *MovingPlatform::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        sf::Vector2f size = m_Mesh->GetSize();
        serialized += std::to_string(m_Type)+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(size.x)+"#";
        serialized += std::to_string(size.y)+"#";
        serialized += std::to_string(m_Animation->GetType())+"#";
        serialized += std::to_string(m_TextureId)+"+";
        return new std::string(serialized);
    }


    MovingPlatform::MovingPlatform(long uuid, int textureId, bool isLocal, Timeline* anchor, bool animationType, sf::Vector2f* position, sf::Vector2f* size):
            Entity(uuid, isLocal, anchor, MOVING_PLATFORM){
        auto* shape = new sf::RectangleShape(sf::Vector2f(size->x, size->y));
        auto* texture = new sf::Texture();
        m_TextureId = textureId;
        if (!texture->loadFromFile("./resources/"+std::to_string(textureId)+".png"))
        {
            std::cout << "Error loading texture" << std::endl;
        }
        shape->setTexture(texture);
        shape->setPosition(position->x, position->y);
        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.shape = shape, specs.isHidden = false;
        m_Mesh = ComponentFactory::AddMesh(specs);  // RENDERING.

        specs.mesh = m_Mesh, specs.isStationary = false, specs.gravityEffect = false;
        specs.collisionType = MOVING_PLATFORM, specs.isActor = false;
        specs.animationType = animationType;

        m_Physics = ComponentFactory::AddPhysics(specs);     // PHYSICS.
        m_Collision = ComponentFactory::AddCollision(specs);    // COLLISION.
        m_Animation = ComponentFactory::AddAnimation(specs);    // ANIMATION.
    }

    void MovingPlatform::Update() {
        int64_t currTime = m_Timeline->getTime();
        int64_t delta = currTime - m_LastTime;
        m_LastTime = currTime;
        m_Delta = delta;
        EventManager::curr_uuid = m_UUID;
        m_Animation->Animate(r_ScriptManager, delta);
    }

    void MovingPlatform::Draw(sf::RenderWindow &window) {
        m_Mesh->Draw(window);
    }

    void MovingPlatform::OnEvent(float posX, float posY) {
        sf::Vector2f location(posX, posY);
        m_Mesh->Place(Mesh::ABSOLUTE, location);
    }

    std::string MovingPlatform::Sync() {
        std::string sync;
        sync += std::to_string(m_UUID)+"#";
        sync += std::to_string(m_Mesh->GetPosition().x)+"#";
        sync += std::to_string(m_Mesh->GetPosition().y)+"+";
        return sync;
    }

    void FixedPlatform::Release() {

    }


    void MovingPlatform::Release() {

    }
}