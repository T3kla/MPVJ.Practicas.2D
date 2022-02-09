#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "litegfx.h"
#include "stb_image.h"

#include "game.h"
#include "scene_01.h"

int Main(void)
{
    Scene_01::Load();
    Game::Run();

    return 0;
}
