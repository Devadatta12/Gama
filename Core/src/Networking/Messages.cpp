#include "Network.h"
#include "Messages.h"
#include "iostream"


namespace gama {



    zmq::message_t EngineMessages::JoinRequest() {
        auto request = zmq::message_t(1);
        memcpy (request.data(), "J", 1);
        return request;
    }

    zmq::message_t EngineMessages::SyncRequest() {
        auto request = zmq::message_t(1);
        memcpy (request.data(), "S", 1);
        return request;
    }

    zmq::message_t EngineMessages::SendPeerExit(Event &event) {
        std::string message;
        message = "PEER|D";
        message += *event.networkEvent.message;
        auto request = zmq::message_t(message.size());
        memcpy (request.data(), message.c_str(), message.size());
        return request;
    }

    zmq::message_t EngineMessages::SendPeerEvent(Event &event) {
        std::string message;
        message = "PEER|U";
        message += *event.networkEvent.message;
        auto request = zmq::message_t(message.size());
        memcpy (request.data(), message.c_str(), message.size());
        return request;
    }

    zmq::message_t EngineMessages::SendUpdateEvent(Event& event) {
        std::string message;
        if (event.type == Event::EventClientLeft){
            message = "D|";
        } else{
            message = "U|";
        }
        message += *event.networkEvent.message;
        auto request = zmq::message_t(message.size());
        memcpy (request.data(), message.c_str(), message.size());
        return request;
    }


    std::string EngineMessages::JoinCharacter(std::string &message) {

        return std::string();
    }


}

