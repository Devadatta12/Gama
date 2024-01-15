#pragma once

namespace gama {
    class EngineMessages{
    public:
        // Messages received by Server.
        constexpr const static char JOIN = 'J';
        constexpr const static char UPDATE_EVENT = 'U';
        constexpr const static char DELETE = 'D';

        constexpr const static char WORLD = 'W';

        constexpr const static int HEADER_LIMIT = 1;
        static zmq::message_t JoinRequest();
        static zmq::message_t SyncRequest();
        static zmq::message_t SendUpdateEvent(Event& event);
        static zmq::message_t SendPeerEvent(Event& event);
        static zmq::message_t SendPeerExit(Event& event);
        static void SyncWorld(std::string& message);
        static std::string JoinCharacter(std::string& message);
    };
}