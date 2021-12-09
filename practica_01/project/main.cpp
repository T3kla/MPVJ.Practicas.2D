#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "engine.h"
#include "litegfx.h"
#include "practica_01.h"
#include "practica_02.h"
#include "stb_image.h"

int main() {
  // auto practica_01 = P01();
  auto practica_02 = P02();

  Engine::Run();

  return 0;
}
