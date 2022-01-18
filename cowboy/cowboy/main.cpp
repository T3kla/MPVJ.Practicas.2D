#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "litegfx.h"
#include "stb_image.h"

#include "engine.h"
#include "scene.h"

int main() {
  auto scene01 = Scene();
  Engine::Run();
}
