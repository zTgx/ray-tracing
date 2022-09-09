
#include "utils.h"

#include "ppm.h"
#include "world.h"
#include "color.h"
#include "context.h"
#include "render.h"

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Context
    Context* context = new Context(aspect_ratio, image_width, image_height);

    // World
    World* world = NewWorld();

    // Render PPM
    Renderer::Draw(context, world);

    std::cerr << "\nDone.\n";
}