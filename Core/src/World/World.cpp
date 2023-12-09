#include "World.h"
#include "Utils.h"
#include "set"

namespace gama {

    void World::Initialize() {
        std::lock_guard<std::mutex> lock(*m_Mutex);

        if (m_Peer != 0){
            EventManager::GetInstance()->Register(this, PEER_WORLD_EVENTS);

            Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 1,true, m_Anchor,
                                                       new sf::Vector2f(0.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 2, true, m_Anchor,
                                                       new sf::Vector2f(266.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 3, true, m_Anchor,
                                                       new sf::Vector2f(532.f, 500.f),
                                                       new sf::Vector2f(268.f, 100.f));

            auto* platformTimeline = new Timeline(nullptr, 17);


            Entity* movingPlatform1 = new MovingPlatform(++SEQ, true, platformTimeline, false,
                                                         new sf::Vector2f(300.f, 350.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* movingPLatform2 = new MovingPlatform(++SEQ, true, platformTimeline, true,
                                                         new sf::Vector2f(450.f, 200.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                    new sf::Vector2f(2.f, 600.f));
            Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                     new sf::Vector2f(2.f, 600.f));
            Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));
            Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));

            Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(600.f, 1.f));

            sf::Vector2f spawnLoc = m_Specs.spawnObjects[m_Peer-1];

            Entity* character = nullptr;
            Entity* spawnObj = nullptr;
            character = new Character(++SEQ+10*m_Peer, true,
                                      m_Anchor,
                                      new sf::Vector2f(spawnLoc.x, spawnLoc.y));
            spawnObj = new SpawnPoint(++SEQ, true, spawnLoc.x, spawnLoc.y);



            m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                               {movingPLatform2->GetUUID(), movingPLatform2},
                               {fixedPlatform1->GetUUID(), fixedPlatform1},
                               {fixedPlatform2->GetUUID(), fixedPlatform2},
                               {fixedPlatform3->GetUUID(), fixedPlatform3},
                               {sideBoundary1->GetUUID(), sideBoundary1},
                               {sideBoundary2->GetUUID(), sideBoundary2},
                               {deathZone1->GetUUID(), deathZone1},
                               {deathZone2->GetUUID(), deathZone2},
                               {deathZone3->GetUUID(), deathZone3},
                               {spawnObj->GetUUID(), spawnObj},
                               {character->GetUUID(), character}});

        } else{
            if (m_IsServer){
                EventManager::GetInstance()->Register(this, SERVER_WORLD_EVENTS);

                Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 1,true, m_Anchor,
                                                           new sf::Vector2f(0.f, 500.f),
                                                           new sf::Vector2f(266.f, 100.f));
                Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 2, true, m_Anchor,
                                                           new sf::Vector2f(266.f, 500.f),
                                                           new sf::Vector2f(266.f, 100.f));
                Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 3, true, m_Anchor,
                                                           new sf::Vector2f(532.f, 500.f),
                                                           new sf::Vector2f(268.f, 100.f));

                Entity* movingPlatform1 = new MovingPlatform(++SEQ, true, m_Anchor, false,
                                                             new sf::Vector2f(300.f, 350.f),
                                                             new sf::Vector2f(20.f, 60.f));
                Entity* movingPLatform2 = new MovingPlatform(++SEQ, true, m_Anchor, true,
                                                             new sf::Vector2f(450.f, 200.f),
                                                             new sf::Vector2f(20.f, 60.f));


//        Entity* spawnPoint = new SpawnPoint(++SEQ, true, 120, 350);
                Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                        new sf::Vector2f(2.f, 600.f));
                Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                         new sf::Vector2f(2.f, 600.f));
                Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));
                Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));

                Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(600.f, 1.f));

                m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                                   {movingPLatform2->GetUUID(), movingPLatform2},
                                   {fixedPlatform1->GetUUID(), fixedPlatform1},
                                   {fixedPlatform2->GetUUID(), fixedPlatform2},
                                   {fixedPlatform3->GetUUID(), fixedPlatform3},
                                   {sideBoundary1->GetUUID(), sideBoundary1},
                                   {sideBoundary2->GetUUID(), sideBoundary2},
                                   {deathZone1->GetUUID(), deathZone1},
                                   {deathZone2->GetUUID(), deathZone2},
                                   {deathZone3->GetUUID(), deathZone3}});
            } else {
                EventManager::GetInstance()->Register(this, CLIENT_WORLD_EVENTS);
            }
        }
        m_LastUpdateTime = m_Anchor->getTime();
    }

    void World::Update() {
        std::lock_guard<std::mutex> lock(*m_Mutex);
        int64_t currTime = m_Anchor->getTime();
        int64_t delta = currTime - m_LastUpdateTime;
        if (delta < 1){
            return;
        }
        m_LastUpdateTime = currTime;

        std::set<long> deletedEntities;
        for (auto entity: m_Entities) {
            if (entity.second->IsLocal()){
                entity.second->Update();

                if ((!m_IsServer || m_Peer!=0) && entity.second->GetType() == CHARACTER){
                    Event updateWorld(Event::EventLocalUpdate, 0);
                    std::string syncM = entity.second->Sync();
                    syncM = syncM.substr(0, syncM.size()-1);
                    updateWorld.networkEvent.message = new std::string(syncM);
                    EventManager::GetInstance()->Execute(updateWorld);
                }
            } else if((m_IsServer || m_Peer!=0) && entity.second->GetType() == CHARACTER){
                entity.second->IncHeartbeat();
                if (entity.second->GetHeartbeat() > 120){
                    std::cout<<"Heartbeat... "<< entity.second->GetHeartbeat()<<std::endl;
                    deletedEntities.insert(entity.first);
                }
            }
        }

        for (auto deletedId: deletedEntities){
            Entity* deletedEntity = m_Entities.find(deletedId)->second;
            deletedEntity->Release();
            m_Entities.erase(deletedId);
        }
    }

    void World::OnEvent(Event& event) {
        std::lock_guard<std::mutex> lock(*m_Mutex);
        switch (event.type) {
            case Event::EventCharacterJoin:
            {
                std::string response;
                long newUUID = ++SEQ;
                // A Spawn Point attached to the Character.
                sf::Vector2f spawnLoc = m_Specs.spawnObjects.front();
                m_Specs.spawnObjects.pop_front();
                for (auto entity: m_Entities) {
                    response += *entity.second->Serialize();
                }
                Entity* character = nullptr;
                Entity* spawnObj = nullptr;
                character = new Character(newUUID, false,
                                              m_Anchor,
                                              new sf::Vector2f(spawnLoc.x, spawnLoc.y));
                spawnObj = new SpawnPoint(++SEQ, false, spawnLoc.x, spawnLoc.y);

                response = "L"+*character->Serialize()+*spawnObj->Serialize()+response;
                response = response.substr(0, response.size() - 1);
                m_Entities.insert({character->GetUUID(), character});
                m_Entities.insert({spawnObj->GetUUID(), spawnObj});
                event.worldEvent.message = new std::string(response);
                break;
            }
            case Event::EventCreateWorld:
            {
                std::string* serializeWorld = event.worldEvent.message;
                std::vector<std::string> entities = tokenize(*serializeWorld, "+");
                for (auto entity: entities) {
                    Entity* newEntity = EntityFactory::Construct(m_Anchor, entity);
                    m_Entities.insert({newEntity->GetUUID(), newEntity});
                }
                break;
            }
            case Event::EventSyncWorld:
            {
                std::string* worldUpdates = event.worldEvent.message;
                std::vector<std::string> entityUpdates = tokenize(*worldUpdates, "+");
                std::set<long> uuids;
                std::set<long> deletedEntities;
                for (const auto& entityUpdate: entityUpdates) {
                    std::vector<std::string> tokens = tokenize(entityUpdate, "#");
                    long uuid = std::stol(tokens[0]);
                    float posX = std::stof(tokens[1]);
                    float posY = std::stof(tokens[2]);
                    uuids.insert(uuid);
                    // If the uuid is not there in m_Entities then this is a new character.
                    if (m_Entities.find(uuid) == m_Entities.end()){
                        Entity* character = new Character(uuid, false, m_Anchor,
                                                          new sf::Vector2f(posX, posY));
                        m_Entities.insert({character->GetUUID(), character});
                    } else {
                        Entity* entity = m_Entities.find(uuid)->second;
                        if (!entity->IsLocal()){
                            entity->OnEvent(posX, posY);
                        }
                    }
                }

                // If a character was deleted.
                for (auto entity: m_Entities) {
                    if (uuids.find(entity.first) == uuids.end() && entity.second->GetType() == CHARACTER){
                        deletedEntities.insert(entity.first);
                    }
                }
                for (auto deletedId: deletedEntities){
                    Entity* deletedEntity = m_Entities.find(deletedId)->second;
                    deletedEntity->Release();
                }
                break;
            }
            case Event::EventCharacterUpdate:
            {
                std::string* characterUpdate = event.worldEvent.message;
                std::vector<std::string> tokens = tokenize(*characterUpdate, "#");
                long uuid = std::stol(tokens[0]);
                float posX = std::stof(tokens[1]);
                float posY = std::stof(tokens[2]);
                auto entity = m_Entities.find(uuid);
                if (entity != m_Entities.end()){
                    entity->second->OnEvent(posX, posY);
                    if (m_IsServer || m_Peer!=0)
                        entity->second->ResetHeartbeat();
                } else if(m_Peer != 0){
                    Entity* character = new Character(uuid, false, m_Anchor,
                                                      new sf::Vector2f(posX, posY));
                    m_Entities.insert({character->GetUUID(), character});
                }
                break;
            }
            case Event::EventSendWorld:
            {
                std::string response;
                for (auto entity: m_Entities) {
                    response += entity.second->Sync();
                }
                response = response.substr(0, response.size() - 1);

                event.worldEvent.message = new std::string(response);
                break;
            }
            case Event::EventCharacterLeaves:
            {
                for (auto entity: m_Entities) {
                    if (entity.second->IsLocal() && entity.second->GetType() == CHARACTER){
                        int64_t globalTime = m_Anchor->getGlobalTime();
                        std::string characterLeaves = std::to_string(entity.first);
                        Event characterEvent(Event::EventClientLeft, globalTime);
                        characterEvent.networkEvent.message = new std::string(characterLeaves);
                        EventManager::GetInstance()->Raise(characterEvent);
                        break;
                    }
                }
                break;
            }
            case Event::EventCharacterDelete:
            {
                std::string* characterUpdate = event.worldEvent.message;
                long uuid = std::stol(*characterUpdate);
                if (m_Entities.find(uuid) != m_Entities.end()){
                    m_Entities.find(uuid)->second->Release();
                }
                m_Entities.erase(uuid);
                break;
            }
            case Event::EventUpdateTime:
            {
                m_LastUpdateTime = m_Anchor->getTime();
            }
            default:
                break;
        }
    }

    void World::Shutdown() {

    }

    std::string World::Serialize() {
        return "nullptr";
    }

}
