#include "sprite_loader.h"

static constexpr char *fileBG = "../resources/txBG.png";
static constexpr char *fileSheet = "../resources/sprSheet.png";

Sprite SpriteLoader::sprBg;

std::vector<Sprite> SpriteLoader::sprBalls;
std::vector<Sprite> SpriteLoader::sprExpls;

Sprite SpriteLoader::sprPlayerIdle;
std::vector<Sprite> SpriteLoader::sprPlayerMoveL;
std::vector<Sprite> SpriteLoader::sprPlayerMoveR;
std::vector<Sprite> SpriteLoader::sprPlayerShootL;
std::vector<Sprite> SpriteLoader::sprPlayerShootR;
Sprite SpriteLoader::sprPlayerHitL;
Sprite SpriteLoader::sprPlayerHitR;

std::vector<Sprite> SpriteLoader::sprHook;

ltex_t *SpriteLoader::txBg = nullptr;
ltex_t *SpriteLoader::txSheet = nullptr;
ltex_t *SpriteLoader::txSheetRev = nullptr;

SpriteLoader SpriteLoader::Instance;

void Reverse(void *start, int bytes, int length)
{
    unsigned char buffer[128];

    unsigned char *lo = (unsigned char *)start;
    unsigned char *hi = (unsigned char *)start + (length - 1) * bytes;

    while (lo < hi)
    {
        memcpy(buffer, lo, bytes);
        memcpy(lo, hi, bytes);
        memcpy(hi, buffer, bytes);

        lo += bytes;
        hi -= bytes;
    }
}

void SpriteLoader::LoadTextures()
{
    int w, h, c;

    // BG
    auto *pixels = stbi_load(fileBG, &w, &h, &c, 4);
    if (!pixels)
        throw "Error loading image";
    txBg = ltex_alloc(w, h, 0);
    ltex_setpixels(txBg, pixels);
    stbi_image_free(pixels);

    // Sheet
    pixels = stbi_load(fileSheet, &w, &h, &c, 4);
    if (!pixels)
        throw "Error loading image";
    txSheet = ltex_alloc(w, h, 0);
    ltex_setpixels(txSheet, pixels);

    // Reverse horizontal
    for (size_t i = 0; i < h; i++)
        Reverse(pixels + i * w * c, c, w);

    // SheetRev
    txSheetRev = ltex_alloc(w, h, 0);
    ltex_setpixels(txSheetRev, pixels);
    stbi_image_free(pixels);

    // Sprite mapping
    sprBg = {txBg, Vec2::Zero(), Vec2::One()};

    sprBalls.push_back({txSheet, {0.2f, 0.6f}, {0.6f, 1.0f}});
    sprBalls.push_back({txSheet, {0.2f, 0.4f}, {0.4f, 0.6f}});
    sprBalls.push_back({txSheet, {0.6f, 0.4f}, {0.8f, 0.6f}});
    sprBalls.push_back({txSheet, {0.6f, 0.2f}, {0.8f, 0.4f}});

    sprExpls.push_back({txSheet, {0.6f, 0.6f}, {1.0f, 1.0f}});
    sprExpls.push_back({txSheet, {0.4f, 0.4f}, {0.6f, 0.6f}});
    sprExpls.push_back({txSheet, {0.8f, 0.4f}, {1.0f, 0.6f}});
    sprExpls.push_back({txSheet, {0.8f, 0.2f}, {1.0f, 0.4f}});

    sprPlayerIdle = {txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}};

    sprPlayerMoveL.push_back({txSheetRev, {0.2f, 0.0f}, {0.4f, 0.2f}});
    sprPlayerMoveL.push_back({txSheetRev, {0.0f, 0.0f}, {0.2f, 0.2f}});

    sprPlayerShootL.push_back({txSheetRev, {0.6f, 0.0f}, {0.8f, 0.2f}});
    sprPlayerShootL.push_back({txSheetRev, {0.4f, 0.0f}, {0.6f, 0.2f}});

    sprPlayerMoveR.push_back({txSheet, {0.6f, 0.0f}, {0.8f, 0.2f}});
    sprPlayerMoveR.push_back({txSheet, {0.8f, 0.0f}, {1.0f, 0.2f}});

    sprPlayerShootR.push_back({txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}});
    sprPlayerShootR.push_back({txSheet, {0.4f, 0.0f}, {0.6f, 0.2f}});

    sprPlayerHitL = {txSheet, {0.2f, 0.2f}, {0.4f, 0.4f}};
    sprPlayerHitR = {txSheet, {0.4f, 0.2f}, {0.6f, 0.4f}};

    sprHook.push_back({txSheet, {0.0f, 0.0f}, {0.1f, 1.0f}});
    sprHook.push_back({txSheet, {0.1f, 0.0f}, {0.2f, 1.0f}});
}

void SpriteLoader::UnloadTextures()
{
    ltex_free(txBg);
    ltex_free(txSheet);
    ltex_free(txSheetRev);
    txBg = nullptr;
    txSheet = nullptr;
    txSheetRev = nullptr;
}
