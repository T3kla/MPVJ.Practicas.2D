#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "litegfx.h"
#include "stb_image.h"

#include "game.h"
#include "sprite_loader.h"

int main(void)
{
    Game::Run();

    return 0;
}
