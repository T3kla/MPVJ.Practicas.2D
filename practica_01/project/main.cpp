#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "litegfx.h"
#include "stb_image.h"

#include "engine.h"
#include "practica_01.h"
#include "practica_02.h"

int main() {
  auto practica_01 = P01();
  // auto practica_02 = P02();

  Engine::Run();

  return 0;
}
