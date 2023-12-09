#include "Entities.h"

namespace gama {

    Entity *SideBoundary::Construct(std::string &serialized) {
        bool isLocal = true;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float sizeX = std::stof(tokens[4]);
        float sizeY = std::stof(tokens[5]);

        Entity* sideBoundary = new SideBoundary(uuid, isLocal,
                                          new sf::Vector2f(posX, posY),
                                          new sf::Vector2f(sizeX, sizeY));
        return sideBoundary;
    }

    std::string *SideBoundary::Serialize() {
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

    SideBoundary::SideBoundary(long uuid, bool isLocal, sf::Vector2f *initPos, sf::Vector2f* size):
    Entity(uuid, isLocal, nullptr, SIDE_BOUNDARY) {
        auto* shape = new sf::RectangleShape(sf::Vector2f(size->x, size->y));
        auto* texture = new sf::Texture();
        if (!texture->loadFromFile("./resources/basketball_court_full.png"))
        {
            std::cout << "Error loading texture" << std::endl;
        }
        shape->setTexture(texture);
        shape->setPosition(initPos->x, initPos->y);
        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid, specs.shape = shape, specs.isHidden = true;
        m_Mesh = ComponentFactory::AddMesh(specs);    //RENDERING.
        specs.mesh = m_Mesh, specs.isStationary = true, specs.gravityEffect = false;
        specs.collisionType = SIDE_BOUNDARY, specs.isActor = false;
        m_Physics = ComponentFactory::AddPhysics(specs);     // PHYSICS.
        m_Collision = ComponentFactory::AddCollision(specs);    // COLLISION.
        m_Camera = ComponentFactory::AddCamera(specs);  // CAMERA.
    }

    void SideBoundary::OnEvent(float posX, float posY) {
    }

    void SideBoundary::Update() {

    }

    void SideBoundary::Draw(sf::RenderWindow &window) {
        m_Mesh->Draw(window);
    }

    std::string SideBoundary::Sync() {
        return "";
    }

    void SideBoundary::Release() {

    }
}