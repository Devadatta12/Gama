#include "Engine.h"

int main(){
    auto* engine = new gama::Engine();
    engine->Start();
    engine->Run();
    engine->Stop();
    return 0;
}