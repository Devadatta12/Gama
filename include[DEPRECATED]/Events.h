#pragma once

#include "Components.h"
#include "Timelines.h"
#include "unordered_map"
#include "queue"
#include "iostream"
#include "v8.h"

namespace gama {

    class Event
    {
    public:
        struct RenderingEvent
        {
            Mesh* mesh;
            float spawnX = -1, spawnY = -1;
            long mainUUID = -1;
            long otherUUID = -1;
            int type = -1;
            bool focus = false;
            bool modeToggled = false;
        };

        struct WorldEvent{
            int type = -1;
            int uuid = -1;
            std::string* message = nullptr;
            bool isMyCharacter = false;
        };

        struct ScoringEvent{
            float spawnPointX = -1, spawnPointY = -1;
            long uuid = -1;
            int type = -1;
        };

        struct PhysicsEvent{
            PhysicsBody* physicsBody = nullptr;
            long characterUUID = -1;
            long collidedUUID = -1;
            float collisionResultantX = 0;
            float collisionResultantY = 0;
            float impulseX = 0;
            float impulseY = 0;
            int type = -1;
        };

        struct TimeEvent{
            Timeline* timeline = nullptr;
            int speed = 0;
            int type = -1;
            int key = -1;
            bool pauseToggled = false;
        };

        struct InputEvent{
            int type = -1;
            long characterUUID = -1;
            float dir_x = 0;
            float dir_y = 0;
        };

        struct NetworkEvent{
            std::string* message = nullptr;
        };

        struct CollisionEvent{
            CollisionMesh* collisionMesh = nullptr;
            long uuid = -1;
            bool isActor = false;
        };

        enum EventType
        {
            EventRespawn=0,
            EventCameraFollow,
            EventPinCamera,
            EventAddRendering,
            EventRemoveRendering,
            EventWindowMode,
            EventCharacterJoin,
            EventCharacterUpdate,
            EventCharacterLeaves,
            EventCharacterDelete,
            EventCreateWorld,
            EventSendWorld,
            EventSyncWorld,
            EventDeath,
            EventAddSpawn,
            EventAddPhysics,
            EventResetPhysics,
            EventAddCollision,
            EventRigidCollision,
            EventMovement,
            EventTimeSpeed,
            EventPausePlayToggle,
            EventBindInput,
            EventFocusGained,
            EventFocusLost,
            EventLocalUpdate,
            EventClientLeft,
            EventUpdateTime,
            EventRecord,
            EventStartReplay,
            EventStartRecording,
            EventEndReplay,
            EventCreateProjectile,
            EventIncreaseHealth,/*33*/
            EventScoring,/*34*/

            /* ALL SCRIPTING EVENTS */
            Input,
            Collision,
            Create,
            Update,
            Destroy,
            Render
        };

        Event(EventType type, int64_t priority): type(type), priority(priority){};

        EventType type;
        int64_t priority;

        union
        {
            RenderingEvent renderingEvent;
            WorldEvent worldEvent;
            ScoringEvent scoringEvent;
            PhysicsEvent physicsEvent;
            TimeEvent timeEvent;
            InputEvent inputEvent;
            NetworkEvent networkEvent;
            CollisionEvent collisionEvent;
        };
    };

    class EventComparator{
    public:
        bool operator()(Event const& e1, Event const& e2)
        {
            // return "true" if "e1" is ordered
            // before "e2", for example:
            return e1.priority >= e2.priority;
        }
    };



    const static std::vector<Event::EventType> RENDERING_EVENTS = {Event::EventRespawn,
                                                        Event::EventCameraFollow,
                                                        Event::EventPinCamera,
                                                        Event::EventAddRendering,
                                                        Event::EventRemoveRendering,
                                                        Event::EventWindowMode,
                                                        Event::EventStartRecording,
                                                        Event::EventStartReplay};

    const static std::vector<Event::EventType> COLLISION_EVENTS = {Event::EventAddCollision,
                                                                   Event::EventUpdateTime};

    const static std::vector<Event::EventType> PHYSICS_EVENTS = {Event::EventAddPhysics,
                                                      Event::EventMovement,
                                                      Event::EventRigidCollision,
                                                      Event::EventResetPhysics,
                                                      Event::EventUpdateTime,
                                                      Event::EventStartRecording,
                                                      Event::EventStartReplay};

    const static std::vector<Event::EventType> TIME_EVENTS = {Event::EventTimeSpeed,
                                                   Event::EventPausePlayToggle};

    const static std::vector<Event::EventType> SERVER_WORLD_EVENTS = {Event::EventCharacterDelete,
                                                                      Event::EventCharacterJoin,
                                                                      Event::EventCharacterUpdate,
                                                                      Event::EventSendWorld,
                                                                      Event::EventUpdateTime};

    const static std::vector<Event::EventType> CLIENT_WORLD_EVENTS = {Event::EventSyncWorld,
                                                                      Event::EventCharacterLeaves,
                                                                      Event::EventCreateWorld,
                                                                      Event::EventUpdateTime,
                                                                      Event::EventCreateProjectile,
                                                                      Event::EventIncreaseHealth};

    const static std::vector<Event::EventType> PEER_WORLD_EVENTS = {Event::EventCharacterUpdate,
                                                                    Event::EventCharacterDelete,
                                                                    Event::EventCharacterLeaves,
                                                                    Event::EventUpdateTime};

    const static std::vector<Event::EventType> WORLD_EVENTS = {};

    const static std::vector<Event::EventType> NETWORK_EVENTS = {Event::EventLocalUpdate,
                                                                 Event::EventClientLeft,
                                                                 Event::EventStartReplay,
                                                                 Event::EventEndReplay};

    const static std::vector<Event::EventType> SCORING_EVENTS = {Event::EventDeath, Event::EventAddSpawn,
                                                                 Event::EventScoring};

    const static std::vector<Event::EventType> INPUT_EVENTS = {Event::EventBindInput, Event::EventFocusGained,
                                                               Event::EventFocusLost};
    const static std::vector<Event::EventType> REPLAY_EVENTS = {Event::EventMovement,
                                                                Event::EventPausePlayToggle,
                                                                Event::EventTimeSpeed,
                                                                Event::EventWindowMode,
                                                                Event::EventSyncWorld,
                                                                Event::EventRecord};

    class EventHandler{
    public:
        virtual void OnEvent(Event& event) = 0;
    };


    class EventManager{
    public:
        static void GetCalleeUUID(const v8::FunctionCallbackInfo<v8::Value> &args) {
            std::string context_name("object_context");
            args.GetReturnValue().Set(((int)EventManager::curr_uuid));
        };

        static void GetCollidedUUID(const v8::FunctionCallbackInfo<v8::Value> &args){
            std::string context_name("object_context");
            args.GetReturnValue().Set(((int)EventManager::collided_uuid));
        };

        static void GetCollidedType(const v8::FunctionCallbackInfo<v8::Value> &args){
            std::string context_name("object_context");
            args.GetReturnValue().Set(((int)EventManager::collided_type));
        };

        static void GetInputType(const v8::FunctionCallbackInfo<v8::Value> &args){
            std::string context_name("object_context");
            args.GetReturnValue().Set(((int)EventManager::input_type));
        };

        static long curr_uuid;
        static long collided_uuid;
        static long collided_type;
        static long input_type;
        static void Raise(const v8::FunctionCallbackInfo<v8::Value>& args);
        static EventManager* GetInstance();
        void Initialize(Timeline* anchor);
        void Register(EventHandler* handler, const std::vector<Event::EventType>& events);
        void Dispatch();
        void Execute(Event& event);
        void Raise(Event event);
    private:
        EventManager() = default;
        std::unordered_map<Event::EventType, std::vector<EventHandler*>> m_EventHandlers;
        std::priority_queue<Event, std::vector<Event>, EventComparator> m_EventQueue;
        Timeline* m_GlobalTimeline = nullptr;
        int64_t m_LastDispatchTime = 0;
        static EventManager* s_EventMgr;
    };
}