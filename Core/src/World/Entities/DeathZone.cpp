#include "Entities.h"


namespace gama {


    Entity *DeathZone::Construct(std::string &serialized) {
        bool isLocal = true;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float sizeX = std::stof(tokens[4]);
        float sizeY = std::stof(tokens[5]);

        Entity* deathZone = new DeathZone(uuid, isLocal,
                                         new sf::Vector2f(posX, posY),
                                         new sf::Vector2f(sizeX, sizeY));
        return deathZone;
    }

    std::string *DeathZone::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        sf::Vector2f size = m_Mesh->GetSize();
        serialized += std::to_string(m_Type)+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(size.x)+"#";
        serialized += std::to_string(size.y)+"+";
        return new std::string(serialized);
    }

    DeathZone::DeathZone(long uuid, bool isLocal, sf::Vector2f *position, sf::Vector2f *size):
    Entity(uuid, isLocal, nullptr, DEATH_ZONE) {
        auto* shape = new sf::RectangleShape(sf::Vector2f(size->x, size->y));
        auto* texture = new sf::Texture();
        if (!texture->loadFromFile("./resources/basketball_court_full.png"))
        {
            std::cout << "Error loading texture" << std::endl;
        }
        shape->setTexture(texture);
        shape->setPosition(position->x, position->y);
        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.shape = shape, specs.isHidden = true;
        m_Mesh = ComponentFactory::AddMesh(specs);  // RENDERING.
        specs.mesh = m_Mesh, specs.collisionType = DEATH_ZONE, specs.isActor = false;
        m_Collision = ComponentFactory::AddCollision(specs);    // COLLISION.
    }

    void DeathZone::OnEvent(float posX, float posY) {
    }

    void DeathZone::Update() {

    }

    void DeathZone::Draw(sf::RenderWindow &window) {
        m_Mesh->Draw(window);
    }

    std::string DeathZone::Sync() {
        return "";
    }

    void DeathZone::Release() {

    }

}