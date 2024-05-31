#pragma once

#include "SFML/Graphics.hpp"
#include "ScriptManager.h"

namespace gama {



    class Component {
    public:
        constexpr const static int MESH_COMPONENT = 1;
        constexpr const static int COLLISION_COMPONENT = 2;
        constexpr const static int PHYSICS_COMPONENT = 3;
        constexpr const static int ANIMATION_COMPONENT = 4;
        constexpr const static int CAMERA_COMPONENT = 5;
    };

    class Mesh: public Component{
    public:
        explicit Mesh(sf::Sprite* character):
                m_Sprite(character), m_Shape(nullptr), m_Hidden(false){};
        explicit Mesh(sf::RectangleShape* other, bool isHidden):
                m_Sprite(nullptr), m_Shape(other), m_Hidden(isHidden){};
        ~Mesh(){ delete m_Sprite; delete m_Shape;};
        void Draw(sf::RenderWindow& window);
        void Place(short positioning, sf::Vector2f& location);
        sf::Vector2f GetPosition();
        sf::Vector2f GetSize();
        void Rotate(int angle){

        }
        void SetScale(int scale){
            float factor = ((float)scale)/50;
            if (m_Sprite != nullptr){
                float scaleX = m_Sprite->getScale().x + factor;
                float scaleY = m_Sprite->getScale().y + factor;
                m_Sprite->setScale(sf::Vector2f(scaleX, scaleY));
            }
        };
        sf::FloatRect GetBoundingBox();
        constexpr const static short ABSOLUTE = true;
        constexpr const static short RELATIVE = false;
    private:
        sf::Sprite* m_Sprite;
        sf::RectangleShape* m_Shape;
        bool m_Hidden;
    };

    class CollisionMesh: public Component{
    public:
        explicit CollisionMesh(sf::Sprite* sprite, int type):
                m_Sprite(sprite), m_Shape(nullptr), m_InterfaceType(type){};
        explicit CollisionMesh(sf::RectangleShape* other, int type):
        m_Sprite(nullptr), m_Shape(other), m_InterfaceType(type){};
        ~CollisionMesh(){ delete m_Sprite; delete m_Shape;};
        sf::FloatRect GetBoundingBox() {
            return (m_Sprite != nullptr)? m_Sprite->getGlobalBounds(): m_Shape->getGlobalBounds();
        };
        int GetType() const{return m_InterfaceType;};
    private:
        sf::Sprite* m_Sprite;
        sf::RectangleShape* m_Shape;
        int m_InterfaceType;
    };


    class PhysicsBody: public Component{

    public:
        explicit PhysicsBody(Mesh* mesh, bool isStationary, bool gravityEffect):
                m_Mesh(mesh), m_Stationary(isStationary), m_Gravity(gravityEffect), m_NotOnSurface(true),
                m_Displacement(new sf::Vector2f(0, 0)), m_Velocity(new sf::Vector2f(0, 0)) {};
        ~PhysicsBody(){ m_Mesh = nullptr;};
        void Simulate(int64_t delta) const;

        Mesh* m_Mesh;
        sf::Vector2f* m_Displacement;
        sf::Vector2f* m_Velocity;
        float m_UnitMovementX = 0;
        float m_UnitMovementY = 0;
        bool m_Animated = false;
        bool m_Stationary;
        bool m_Gravity;
        bool m_NotOnSurface;
    };

    class InputComponent: public Component{
    public:
        explicit InputComponent(long uuid): m_CharacterUUID(uuid){};
        long m_CharacterUUID;
    };

    class Animation: public Component{
    public:
        Animation(Mesh* mesh, bool animationType): m_Mesh(mesh), m_AnimationType(animationType) {};
        ~Animation(){ m_Mesh = nullptr;};
        void Animate(ScriptManager* sm,int64_t delta);
        int GetType() const{return (m_AnimationType)?1:0;};
        void SetType(int animationType){m_AnimationType = animationType;};
        int m_Direction = rand()%2;
    private:
        constexpr const static float DEFAULT_VELOCITY = 1;
        Mesh* m_Mesh;
        bool m_AnimationType;
    };

    class Camera: public Component{
    public:
        explicit Camera(long UUID): m_UUID(UUID){};
        ~Camera()= default;
    private:
        long m_UUID;
    };

    class ComponentSpecs{
    public:
        sf::Sprite* sprite = nullptr;
        sf::RectangleShape* shape = nullptr;
        Mesh* mesh = nullptr;
        long uuid = -1;
        float spawnX = -1, spawnY = -1;
        int collisionType = -1;
        bool isActor = false;
        bool isHidden = false;
        bool isStationary = false;
        bool gravityEffect = false;
        bool animationType = false;
    };

    class ComponentFactory{
    public:
        static Mesh* AddMesh(ComponentSpecs& specs);
        static void RemoveMesh(long uuid);
        static PhysicsBody* AddPhysics(ComponentSpecs& specs);
        static Animation* AddAnimation(ComponentSpecs& specs);
        static CollisionMesh* AddCollision(ComponentSpecs& specs);
        static Camera* AddCamera(ComponentSpecs& specs);
        static void AddSpawnPoint(ComponentSpecs& specs);
    };
}