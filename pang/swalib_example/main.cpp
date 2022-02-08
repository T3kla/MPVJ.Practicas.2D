#include "engine.h"
#include "scene_01.h"
#include <iostream>

int Main(void) {

  Scene_01::Load();

  Engine::Run();

  return 0;
}
