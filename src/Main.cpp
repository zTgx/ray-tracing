#include "world.h"
#include "context.h"
#include "props.h"

int main() {
    // Context
    Context* context = new Context(Props{});

    // World
    World* world = NewWorld();

    // Render
    context->Render(world);

    // Relase Resource
    delete world;
    delete context;
}