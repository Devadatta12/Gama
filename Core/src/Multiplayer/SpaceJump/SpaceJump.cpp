#include "Engine.h"
#include "chrono"
#include <v8.h>
#include <libplatform/libplatform.h>
#include <iostream>
#include <cstdio>
#include "v8helpers.h"

void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    bool first = true;
    for (int i = 0; i < args.Length(); i++) {
        // v8::HandleScope handle_scope(args.GetIsolate());
        if (first) {
            first = false;
        } else {
            printf(" ");
        }
        v8::String::Utf8Value str(args.GetIsolate(), args[i]);
        const char* cstr = *str ? *str : "<string conversion failed>";
        printf("%s", cstr);
    }
    printf("\n");
    fflush(stdout);
}

int main(int argc, char *argv[]){
    if (argc == 0){
        std::cout<<"Please selected a game from the game projects."<<std::endl;
    }
    std::string game = "SpaceJump";
    std::cout<<"Command line arguments "<<argc<<std::endl;
    auto* m_EventMgr = gama::EventManager::GetInstance();
    auto* m_Timeline = new gama::Timeline(nullptr, 17);
    m_EventMgr->Initialize(m_Timeline);
    auto* m_TimeKeeper = new gama::TimeKeeper();
    m_TimeKeeper->Initialize();
    m_TimeKeeper->Keep(gama::TimeKeeper::WILDCARD, m_Timeline);
    auto* m_PhysicsEngine = new gama::PhysicsEngine(m_Timeline);
    auto* m_CollisionSystem = new gama::CollisionSystem(m_Timeline);
    gama::NetworkProps networkProps;
    networkProps.eventPort = 5556;
    networkProps.statusPort = 5557;
    networkProps.topology = gama::NetworkProps::CLIENT_SERVER;
    networkProps.role = 1;
    auto* m_NetworkMgr = new gama::NetworkMgr(networkProps);
    auto* m_RenderingEngine = new gama::RenderingEngine();
    auto* m_InputSystem = new gama::InputSystem(m_Timeline);
    auto* m_ScoringSystem = new gama::ScoringSystem();
    auto* m_World = new gama::World(m_Timeline, false, 0, game);
    auto* m_ReplaySystem = new gama::ReplaySystem();
    long m_LastTime = m_Timeline->getTime();


    m_PhysicsEngine->Initialize();
    m_InputSystem->Initialize();
    m_CollisionSystem->Initialize();

    m_RenderingEngine->Initialize(game);
    m_ScoringSystem->Initialize(m_Timeline);
    m_World->Initialize();
    m_NetworkMgr->Initialize();
    m_ReplaySystem->Initialize();

    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.release());
    v8::V8::InitializeICU();
    v8::V8::Initialize();
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate *isolate = v8::Isolate::New(create_params);

    { // anonymous scope for managing handle scope
        v8::Isolate::Scope isolate_scope(isolate); // must enter the virtual machine to do stuff
        v8::HandleScope handle_scope(isolate);

        // Best practice to isntall all global functions in the context ahead of time.
        v8::Local <v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
        // Bind the global 'print' function to the C++ Print callback.
        global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, Print));
        // Bind the global static factory function for creating new GameObject instances
        global->Set(isolate, "Raise",
                    v8::FunctionTemplate::New(isolate, gama::EventManager::Raise));
        global->Set(isolate, "getCalleeUUID",
                    v8::FunctionTemplate::New(isolate, gama::EventManager::GetCalleeUUID));

        // Bind the global static function for retrieving object handles
        global->Set(isolate, "gethandle", v8::FunctionTemplate::New(isolate, ScriptManager::getHandleFromScript));
        v8::Local <v8::Context> default_context = v8::Context::New(isolate, NULL, global);
        v8::Context::Scope default_context_scope(default_context); // enter the context

        auto sm = new ScriptManager(isolate, default_context);

        // Without parameters, these calls are made to the default context
        sm->addScript("Input", "./GameProjects/"+game+"/Input.js");
        // Create a new context
        //long characterUUID = m_InputSystem->GetCharacterUUID();

        v8::Local <v8::Context> object_context = v8::Context::New(isolate, NULL, global);
        sm->addContext(isolate, object_context, "object_context");


        m_World->Bind(isolate, object_context);
        m_World->AddScripting(sm);

        // With the "object_context" parameter, these scripts are put in a
        // different context than the prior three scripts
        sm->addScript("Scoring", "./GameProjects/"+game+"/Scoring.js", "object_context");
        sm->addScript("Editing", "./GameProjects/"+game+"/Editing.js", "object_context");
        sm->addScript("Update", "./GameProjects/"+game+"/Update.js", "object_context");

        m_InputSystem->AddScripting(sm);
        m_ScoringSystem->AddScripting(sm);

        while (true) {

            m_EventMgr->Dispatch();
            if (!m_RenderingEngine->PollWindow()) {
                break;
            }
            m_InputSystem->Poll();
            m_World->Update();
            m_CollisionSystem->Detect();
            m_PhysicsEngine->Simulate();
            m_RenderingEngine->Render();
        }

        m_InputSystem->Shutdown();
        m_RenderingEngine->Shutdown();
        m_PhysicsEngine->Shutdown();
        m_CollisionSystem->Shutdown();
        m_ScoringSystem->Shutdown();
        m_NetworkMgr->Shutdown();
        m_World->Shutdown();

    }
    return 0;
}
