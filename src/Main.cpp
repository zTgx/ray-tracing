#include "world.h"
#include "context.h"

int main() {
    const float ratio  = 16.0 / 9.0;
    const int   width  = 1200;
    const int   height = static_cast<int>(width / ratio);

    // Context
    Context* context = new Context(ratio, width, height);

    // World
    World* world = NewWorld();

    // Render
    context->Render(world);

    // Relase Resource
    delete world;
    delete context;

    std::cerr << "\nDone.\n";
}