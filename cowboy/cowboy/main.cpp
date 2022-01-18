#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define NOMINMAX

#include "litegfx.h"
#include "stb_image.h"
#include "stb_truetype.h"
#include <entt/entt.hpp>

#include "engine.h"
#include "scene.h"

int main() {
  auto scene01 = Scene();
  Engine::Run();
}
