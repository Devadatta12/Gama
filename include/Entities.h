#pragma once

#include "SFML/Graphics.hpp"
#include "Components.h"
#include "Timelines.h"
#include "unordered_map"
#include "vector"
#include "iostream"
#include "Utils.h"

namespace gama {

#define LOCAL_CHARACTER_TYPE 'L'
#define CHARACTER_TYPE 'C'


#define CHARACTER 1
#define FIXED_PLATFORM 2
#define MOVING_PLATFORM 3
#define SPAWN_POINT 4
#define DEATH_ZONE 5
#define SIDE_BOUNDARY 6

    class EntityId{
    public:
        long uuid;
        int type;
        EntityId(long uuid, int type): uuid(uuid), type(type){};
    };

    class Entity {
    public:
        Entity(long uuid, bool isLocal, Timeline* anchor, int type): m_Mesh(nullptr),
            m_Physics(nullptr), m_Animation(nullptr), m_Camera(nullptr),
            m_Collision(nullptr), m_Timeline(new Timeline(anchor, 1)),
            m_IsLocal(isLocal), m_UUID(uuid), m_LastTime(0), m_Type(type), m_HeartBeat(0) {};

        virtual void Update() = 0;
        bool IsLocal() const{ return  m_IsLocal;};
        virtual void OnEvent(float posX, float posY) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;
        virtual std::string* Serialize() = 0;
        virtual std::string Sync() = 0;
        virtual void Release() = 0;
        long GetUUID() const{ return m_UUID;};
        int GetType() const{return m_Type;};
        void IncHeartbeat(){m_HeartBeat++;};
        void ResetHeartbeat(){m_HeartBeat = 0;};
        int64_t GetHeartbeat(){return m_HeartBeat;};

        ~Entity() {
            delete m_Mesh;
            delete m_Physics;
            delete m_Animation;
            delete m_Camera;
            delete m_Timeline;
        };
    protected:
        long m_UUID;
        Mesh* m_Mesh;
        PhysicsBody* m_Physics;
        CollisionMesh* m_Collision;
        Animation* m_Animation;
        Camera* m_Camera;
        Timeline* m_Timeline;
        int64_t m_LastTime;
        int64_t m_HeartBeat;
        int m_Type;
        bool m_IsLocal = false;
    };

    class Character: public Entity {
    public:
        static Entity* Construct(Timeline *anchor, std::string& serialized);
        Character(long uuid, bool isLocal, Timeline* anchor, sf::Vector2f* initPos);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;
    };

    class FixedPlatform: public Entity {
    public:
        static Entity* Construct(Timeline *anchor, std::string& serialized);
        FixedPlatform(long uuid, int textureType, bool isLocal, Timeline* anchor, sf::Vector2f* position, sf::Vector2f* size);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;

    private:
        int m_TextureType;
    };

    class MovingPlatform: public Entity {
    public:
        static Entity* Construct(Timeline *anchor, std::string& serialized);
        MovingPlatform(long uuid, bool isLocal, Timeline* anchor, bool animationType, sf::Vector2f* position, sf::Vector2f* size);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;
    };

    class SpawnPoint: public Entity {
    public:
        static Entity* Construct(std::string& serialized);
        SpawnPoint(long uuid, bool isLocal, float x, float y);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;

    private:
        float m_PosX;
        float m_PosY;
    };

    class DeathZone: public Entity {
    public:
        static Entity* Construct(std::string& serialized);
        DeathZone(long uuid, bool isLocal, sf::Vector2f* position, sf::Vector2f* size);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;
    };

    class SideBoundary: public Entity {
    public:
        static Entity* Construct(std::string& serialized);
        SideBoundary(long uuid, bool isLocal, sf::Vector2f* initPos, sf::Vector2f* size);
        void Update() override;
        void Draw(sf::RenderWindow& window) override;
        std::string *Serialize() override;

        void OnEvent(float posX, float posY) override;

        std::string Sync() override;

        void Release() override;
    };

    class EntityFactory{
    public:
        static Entity* Construct(Timeline* anchor, std::string& serializedEntity){
            if (serializedEntity.at(0) == LOCAL_CHARACTER_TYPE){
                return Character::Construct(anchor, serializedEntity);
            }
            int entityType = std::stoi(serializedEntity.substr(0, serializedEntity.find_first_of('#')));
            //TODO:
            switch (entityType) {
                case CHARACTER:{
                    return Character::Construct(anchor, serializedEntity);
                }
                case FIXED_PLATFORM:{
                    return FixedPlatform::Construct(anchor, serializedEntity);
                }
                case MOVING_PLATFORM:{
                    return MovingPlatform::Construct(anchor, serializedEntity);
                }
                case SPAWN_POINT:{
                    return SpawnPoint::Construct(serializedEntity);
                }
                case SIDE_BOUNDARY:{
                    return SideBoundary::Construct(serializedEntity);
                }
                case DEATH_ZONE:{
                    return DeathZone::Construct(serializedEntity);
                }
                default:
                {
                    return nullptr;
                }

            }
        }
    };
}


/*
 * #define DEFAULT_VELOCITY 1

    class Entity {
    public:
        Entity(long uuid, Timeline& timeline);
        Entity(long uuid, sf::Sprite* sprite, Timeline& timeline);
        virtual sf::Drawable* Draw() = 0;
        virtual sf::FloatRect GetGlobalBounds() = 0;
        long GetUuid() const {return m_Uuid;}
        virtual std::string* Serialize() = 0;

    protected:
        sf::RectangleShape *m_Shape;
        sf::Sprite *m_Sprite;
        Timeline* m_Timeline;
        int64_t lastMeasuredTime;

    private:
        long m_Uuid;
    };


    class Transform{
    public:
        Transform(long uuid, float x, float y):uuid(uuid), x(x), y(y){};
        float x;
        float y;
        long uuid;
    };

    class Character: public Entity{
    public:
        static Character* Construct(Timeline* timeline, std::vector<std::string> &tokens, int& iterator);
        Character(long uuid, sf::Sprite* sprite, Timeline& timeline);
        Transform Act(Motion& motion);
        void Act(Transform& transform);
        void Place(float x, float y);
        void Animate();

        std::string *Serialize() override;

        sf::Drawable *Draw() override;

    protected:
        sf::FloatRect GetGlobalBounds() override;
    };

    class MovingPlatform: public Entity{
    public:
        static MovingPlatform* Construct(Timeline* timeline, std::vector<std::string> &tokens, int& iterator);
        MovingPlatform(long uuid, sf::RectangleShape* shape, int direction, Timeline& timeline);
        void Animate();
        void Place(float x, float y);

        std::string *Serialize() override;

        sf::Drawable *Draw() override;

    protected:
        sf::FloatRect GetGlobalBounds() override;

    private:
        int m_Direction;
    };

    class FixedPlatform: public Entity{
    public:
        static FixedPlatform* Construct(Timeline* timeline, std::vector<std::string> &tokens, int& iterator);
        FixedPlatform(long uuid, sf::RectangleShape* shape, Timeline& timeline);

        std::string *Serialize() override;

        sf::Drawable *Draw() override;

    protected:
        sf::FloatRect GetGlobalBounds() override;
    };

    class EntityWorld{
    public:
        void Initialize(Timeline& timeline,const std::string&);
        void Initialize(Timeline& timeline);
        Transform ApplyMotion(Motion& motion);
        void ApplyMotion(long uuid, Transform transform);
        void Animate();
        void AddPlayer(long uuid, Character* otherPlayer);
        Character* CreatePlayer();
        void Update(std::string& players);
        void RemovePlayer(long uuid);
        void Render(sf::RenderWindow& window);
        std::string Sync();
        std::string* Serialize();
        void Deserialize(std::vector<std::string>& tokens);
        long MyUuid();
    private:
        Character* m_Player;
        Timeline* m_Timeline;
        std::unordered_map<long, Character*> m_OtherPlayers;
        std::unordered_map<long, MovingPlatform*> m_MovingPlatforms;
        std::unordered_map<long, FixedPlatform*> m_FixedPlatforms;
        std::mutex* mutex;
        std::vector<sf::Vector2f*> spawnLocations;
        bool m_IsServer;
        long seqId;
        int spawnLocation;
        int totalLocations;
    };
 */