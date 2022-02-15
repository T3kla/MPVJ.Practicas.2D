#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define NOMINMAX

#include "litegfx.h"
#include "stb_image.h"
#include "stb_truetype.h"

#include "game.h"

int main(void)
{
    Game::Run();

    return 0;
}
