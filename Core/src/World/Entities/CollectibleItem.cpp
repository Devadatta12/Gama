#include "Entities.h"

namespace gama{
    Entity *CollectibleItem::Construct(std::string &serialized) {
        bool isLocal = false;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);
        float sizeX = std::stof(tokens[4]);
        float sizeY = std::stof(tokens[5]);
        int texture = std::stoi(tokens[6]);

        Entity* platform = new CollectibleItem(uuid, texture, isLocal,
                                             new sf::Vector2f(posX, posY),
                                             new sf::Vector2f(sizeX, sizeY) );
        return platform;
    }

    CollectibleItem::CollectibleItem(long uuid, int textureId, bool isLocal, sf::Vector2f *position,
                                     sf::Vector2f *size): Entity(uuid, isLocal, nullptr, COLLECTIBLE_ITEM) {
        auto* shape = new sf::RectangleShape(sf::Vector2f(size->x, size->y));
        auto* texture = new sf::Texture();
        m_TextureId = textureId;
        std::string texturePath;
        texturePath = "./resources/"+std::to_string(textureId)+".png";
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
        specs.collisionType = COLLECTIBLE_ITEM, specs.isActor = false;

        m_Collision = ComponentFactory::AddCollision(specs);    // COLLISION.
    }

    void CollectibleItem::Update() {
        // Do Nothing.
    }

    void CollectibleItem::Draw(sf::RenderWindow &window) {
        m_Mesh->Draw(window);
    }

    std::string *CollectibleItem::Serialize() {
        std::string serialized;
        sf::Vector2f position = m_Mesh->GetPosition();
        sf::Vector2f size = m_Mesh->GetSize();
        serialized += std::to_string(m_Type)+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(position.x)+"#";
        serialized += std::to_string(position.y)+"#";
        serialized += std::to_string(size.x)+"#";
        serialized += std::to_string(size.y)+"#";
        serialized += std::to_string(m_TextureId)+"+";
        return new std::string(serialized);
    }

    void CollectibleItem::OnEvent(float posX, float posY) {

    }

    std::string CollectibleItem::Sync() {
        return "";
    }

    void CollectibleItem::Release() {

    }
}