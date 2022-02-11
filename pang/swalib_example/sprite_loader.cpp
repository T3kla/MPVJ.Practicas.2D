#include "sprite_loader.h"

const char *fileBG = "resources/txBG.png";
const char *fileSheet = "resources/sprSheet.png";

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

stbi_uc *SpriteLoader::pixels = nullptr;
ltex_t *SpriteLoader::txBg = nullptr;
ltex_t *SpriteLoader::txSheet = nullptr;

SpriteLoader SpriteLoader::Instance;

void SpriteLoader::LoadTextures()
{
    int w, h, c;

    // BG
    pixels = stbi_load(fileBG, &w, &h, &c, 4);
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

    // Sheet Reverse
    pixels = stbi_load(fileSheet, &w, &h, &c, 4);

    for (size_t i = 0; i < length; i++)
    {

    }

    ltex_setpixels(txSheet, pixels);
    stbi_image_free(pixels);

    //

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
    ltex_free()
}
