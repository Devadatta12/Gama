#include "Entities.h"

namespace gama{

    Entity *SpawnPoint::Construct(std::string &serialized) {
        bool isLocal = true;
        std::vector<std::string> tokens = tokenize(serialized, "#");
        long uuid = std::stol(tokens[1]);
        float posX = std::stof(tokens[2]);
        float posY = std::stof(tokens[3]);

        std::cout<<"Spawn Point Constructed "<<posX<<","<<posY<<std::endl;

        Entity* spawnPoint = new SpawnPoint(uuid, isLocal, posX, posY );
        return spawnPoint;
    }

    std::string *SpawnPoint::Serialize() {
        std::string serialized;
        serialized += std::to_string(m_Type)+"#";
        serialized += std::to_string(m_UUID)+"#";
        serialized += std::to_string(m_PosX)+"#";
        serialized += std::to_string(m_PosY)+"+";
        return new std::string(serialized);
    }

    SpawnPoint::SpawnPoint(long uuid, bool isLocal, float x, float y):
            Entity(uuid, isLocal, nullptr, SPAWN_POINT) {
        m_PosX = x, m_PosY = y;
        // Initialize Components.
        ComponentSpecs specs{};
        specs.uuid = uuid;
        specs.spawnX = x;
        specs.spawnY = y;
        ComponentFactory::AddSpawnPoint(specs);     // SPAWN COMPONENT.
    }


    void SpawnPoint::Update() {
        // DO NOTHING.
    }

    void SpawnPoint::OnEvent(float posX, float posY) {
    }

    void SpawnPoint::Draw(sf::RenderWindow &window) {
        // DO NOTHING.
    }

    std::string SpawnPoint::Sync() {
        return "";
    }

    void SpawnPoint::Release() {

    }
}