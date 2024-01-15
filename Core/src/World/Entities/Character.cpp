#include "Entities.h"
#include "Events.h"

namespace gama{

    Entity *Character::Construct(Timeline *anchor, std::string &serialized) {
        bool isLocal = false;
        if (serialized.at(0) == 'L'){
            serialized = serialized.substr(1);
            isLocal = true;
        }
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        int textureId = std::stoi(tokens[4]);
        bool gravity = std::stoi(tokens[5]);

        Entity* character = new Character(uuid, isLocal, anchor, new sf::Vector2f(posX, posY), textureId, gravity);
        if (isLocal){
            Event cameraEvent(Event::EventRespawn, 0);
            cameraEvent.renderingEvent.mainUUID = character->GetUUID();
            cameraEvent.renderingEvent.spawnX = posX;
            cameraEvent.renderingEvent.spawnY = posY;
            cameraEvent.renderingEvent.focus = true;
            EventManager::GetInstance()->Execute(cameraEvent);
        }
        return character;
    }

    std::string *Character::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        serialized += std::to_string(GetType())+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(m_TextureId)+"#";
        serialized += std::to_string(m_Gravity)+"+";
        return new std::string(serialized);
    }

    Character::Character(long uuid, bool isLocal, Timeline *anchor, sf::Vector2f *initPos,
                         int texture_id, bool gravity) :
    Entity(uuid, isLocal, anchor, CHARACTER) {
        m_TextureId = texture_id;
        m_Gravity = gravity;
        auto* sprite = new sf::Sprite();
        auto* texture = new sf::Texture();
        if (!texture->loadFromFile("./resources/"+std::to_string(texture_id)+".png"))
        {
            std::cout << "Error loading texture" << std::endl;
        }
        sprite->setTexture(*texture);
        sprite->setPosition(initPos->x, initPos->y);
        sprite->scale(0.13,0.2);

        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.sprite = sprite;
        m_Mesh = ComponentFactory::AddMesh(specs);  // RENDERING.

        specs.mesh = m_Mesh, specs.isStationary = false, specs.gravityEffect = gravity;
        specs.collisionType = CHARACTER, specs.isActor = true;

        if (isLocal){
            m_Physics = ComponentFactory::AddPhysics(specs);    // PHYSICS.
            m_Collision = ComponentFactory::AddCollision(specs);      // COLLISION.
            Event inputEvent(Event::EventBindInput, 0);                // INPUT.
            inputEvent.inputEvent.characterUUID = uuid;
            EventManager::GetInstance()->Execute(inputEvent);
            Event cameraEvent(Event::EventRespawn, 0);
            cameraEvent.renderingEvent.mainUUID = GetUUID();
            cameraEvent.renderingEvent.spawnX = m_Mesh->GetPosition().x;
            cameraEvent.renderingEvent.spawnY = m_Mesh->GetPosition().y;
            cameraEvent.renderingEvent.focus = true;
            EventManager::GetInstance()->Execute(cameraEvent);
        }
    }

    void Character::Update() {
        int64_t currTime = m_Timeline->getTime();
        int64_t delta = currTime - m_LastTime;
        m_LastTime = currTime;
        m_Physics->Simulate(delta);
    }

    void Character::OnEvent(float posX, float posY) {
        sf::Vector2f location(posX, posY);
        m_Mesh->Place(Mesh::ABSOLUTE, location);
    }

    void Character::Draw(sf::RenderWindow& window) {
        m_Mesh->Draw(window);
    }

    std::string Character::Sync() {
        std::string sync;
        sync += std::to_string(m_UUID)+"#";
        sync += std::to_string(m_Mesh->GetPosition().x)+"#";
        sync += std::to_string(m_Mesh->GetPosition().y)+"#";
        sync += std::to_string(m_TextureId)+"#";
        sync += std::to_string(m_Gravity)+"+";
        return sync;
    }

    void Character::Release() {
        ComponentFactory::RemoveMesh(m_UUID);
    }

}

