#include "Engine.h"
#include "chrono"
#include "iostream"

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

int main(){
    std::string game = "GrandMotoTorque";
    auto* m_EventMgr = gama::EventManager::GetInstance();
    auto* m_Timeline = new gama::Timeline(nullptr, 17);
    m_EventMgr->Initialize(m_Timeline);
    auto* m_TimeKeeper = new gama::TimeKeeper();
    m_TimeKeeper->Initialize();
    m_TimeKeeper->Keep(gama::TimeKeeper::WILDCARD, m_Timeline);
    gama::NetworkProps networkProps;
    networkProps.eventPort = 5556;
    networkProps.statusPort = 5557;
    networkProps.topology = gama::NetworkProps::CLIENT_SERVER;
    networkProps.role = 2;
    auto* m_NetworkMgr = new gama::NetworkMgr(networkProps);
    auto* m_World = new gama::World(m_Timeline, true, 0, game);
    long m_LastTime = m_Timeline->getTime();

    std::cout<<"Initializing"<<std::endl;


    m_World->Initialize();
    m_NetworkMgr->Initialize();

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
        v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
        // Bind the global 'print' function to the C++ Print callback.
        global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, Print));
        // Bind the global static factory function for creating new GameObject instances
        global->Set(isolate, "Raise",
                    v8::FunctionTemplate::New(isolate, gama::EventManager::Raise));
        // Bind the global static function for retrieving object handles
        global->Set(isolate, "getCalleeUUID",
                    v8::FunctionTemplate::New(isolate, gama::EventManager::GetCalleeUUID));
        global->Set(isolate, "gethandle", v8::FunctionTemplate::New(isolate, ScriptManager::getHandleFromScript));
        v8::Local<v8::Context> default_context = v8::Context::New(isolate, NULL, global);
        v8::Context::Scope default_context_scope(default_context); // enter the context

        auto sm = new ScriptManager(isolate, default_context);

        v8::Local<v8::Context> object_context = v8::Context::New(isolate, NULL, global);
        sm->addContext(isolate, object_context, "object_context");

        m_World->Bind(isolate, object_context);
        m_World->AddScripting(sm);

        sm->addScript("Animation", "./GameProjects/"+game+"/Animation.js", "object_context");

        std::cout << "Started" << std::endl;

        while (true) {
            m_EventMgr->Dispatch();
            m_World->Update();
        }
    }


    m_NetworkMgr->Shutdown();
    m_World->Shutdown();

    return 0;
}
