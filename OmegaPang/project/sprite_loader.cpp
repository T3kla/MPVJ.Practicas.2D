#include "sprite_loader.h"

#include "stb_image.h"
#include "texture.h"

Sprite SpriteLoader::sprBg;
Sprite SpriteLoader::sprPlayerIdle;
Sprite SpriteLoader::sprPlayerHitL;
Sprite SpriteLoader::sprPlayerHitR;
Sprite SpriteLoader::sprSqr;
Sprite SpriteLoader::sprCrl;
Sprite SpriteLoader::sprBox;
Sprite SpriteLoader::sprBall;
Sprite SpriteLoader::sprBee;
Sprite SpriteLoader::sprLevel;
Sprite SpriteLoader::sprTrees1;
Sprite SpriteLoader::sprTrees2;
Sprite SpriteLoader::sprCloud;
Sprite SpriteLoader::sprMapPlayerIdle;
Sprite SpriteLoader::sprMapGUI_06;
Sprite SpriteLoader::sprMapGUI_08;
Sprite SpriteLoader::sprMapGUI_09;
Sprite SpriteLoader::sprMapGUI_11;
Sprite SpriteLoader::sprMapGUI_16;
Sprite SpriteLoader::sprMapGUI_17;
Sprite SpriteLoader::sprMapGUI_18;
Sprite SpriteLoader::sprMapGUI_19;
Sprite SpriteLoader::sprMapGUI_29;
std::vector<Sprite> SpriteLoader::sprBalls;
std::vector<Sprite> SpriteLoader::sprExpls;
std::vector<Sprite> SpriteLoader::sprPlayerMoveL;
std::vector<Sprite> SpriteLoader::sprPlayerMoveR;
std::vector<Sprite> SpriteLoader::sprPlayerShootL;
std::vector<Sprite> SpriteLoader::sprPlayerShootR;
std::vector<Sprite> SpriteLoader::sprHook;
std::vector<Sprite> SpriteLoader::sprSheetBee;
std::vector<Sprite> SpriteLoader::sprMapPlayerRun;

SpriteLoader SpriteLoader::Instance;
std::vector<Texture> SpriteLoader::Textures;

void Load(const char *file, ltex_t *&texture, unsigned char *&alphaMap, int &w, int &h)
{
    int c;

    stbi_uc *pixels;

    pixels = stbi_load(file, &w, &h, &c, 4);

    if (!pixels)
        throw "Error loading image";

    alphaMap = new unsigned char[w * h];

    for (int i = 0; i < w * h; i++)
        alphaMap[i] = pixels[i * 4 + 3];

    texture = ltex_alloc(w, h, 0);
    ltex_setpixels(texture, pixels);
    stbi_image_free(pixels);
}

void SpriteLoader::LoadTexture(const char *name, const char *file)
{
    ltex_t *tx = nullptr;
    unsigned char *alpha = nullptr;
    int w, h;

    Load(file, tx, alpha, w, h);

    Textures.push_back({name, tx, alpha, w, h});
}

Texture *SpriteLoader::GetTexture(const char *name)
{
    for (auto &texture : Textures)
        if (strcmp(texture.name, name) == 0)
            return &texture;

    return nullptr;
}

void SpriteLoader::UnloadTextures()
{
    for (auto &texture : Textures)
    {
        delete texture.name;
        ltex_free(texture.texture);
    }

    Textures.clear();
}

void SpriteLoader::SetSprites()
{
    auto *txBg = GetTexture("txBG.png");
    auto *txSheetPang = GetTexture("sheetPang.png");
    auto *txSheetBee = GetTexture("sheetBee.png");

    auto *txColSqr = GetTexture("rect.png");
    auto *txColCrl = GetTexture("circle.png");
    auto *txColBall = GetTexture("ball.png");
    auto *txColBox = GetTexture("box.png");

    auto *txBee = GetTexture("bee.png");
    auto *txLevel = GetTexture("level.png");
    auto *txTrees1 = GetTexture("trees1.png");
    auto *txTrees2 = GetTexture("trees2.png");
    auto *txClouds = GetTexture("clouds.png");

    auto *txPlayerIdle = GetTexture("idle.png");
    auto *txPlayerRun = GetTexture("run.png");
    auto *txTileset = GetTexture("tiles.png");

    // Sprite mapping
    sprBg = {txBg, Vec2::Zero(), Vec2::One()};

    sprBalls.reserve(4);
    sprBalls.push_back({txSheetPang, {0.2f, 0.6f}, {0.6f, 1.0f}});
    sprBalls.push_back({txSheetPang, {0.2f, 0.4f}, {0.4f, 0.6f}});
    sprBalls.push_back({txSheetPang, {0.6f, 0.4f}, {0.8f, 0.6f}});
    sprBalls.push_back({txSheetPang, {0.6f, 0.2f}, {0.8f, 0.4f}});

    sprExpls.reserve(4);
    sprExpls.push_back({txSheetPang, {0.6f, 0.6f}, {1.0f, 1.0f}});
    sprExpls.push_back({txSheetPang, {0.4f, 0.4f}, {0.6f, 0.6f}});
    sprExpls.push_back({txSheetPang, {0.8f, 0.4f}, {1.0f, 0.6f}});
    sprExpls.push_back({txSheetPang, {0.8f, 0.2f}, {1.0f, 0.4f}});

    sprPlayerIdle = {txSheetPang, {0.2f, 0.0f}, {0.4f, 0.2f}};

    sprPlayerMoveR.reserve(2);
    sprPlayerMoveR.push_back({txSheetPang, {0.6f, 0.0f}, {0.8f, 0.2f}});
    sprPlayerMoveR.push_back({txSheetPang, {0.8f, 0.0f}, {1.0f, 0.2f}});
    sprPlayerMoveL.reserve(2);
    sprPlayerMoveL.push_back({txSheetPang, {0.8f, 0.0f}, {0.6f, 0.2f}});
    sprPlayerMoveL.push_back({txSheetPang, {1.0f, 0.0f}, {0.8f, 0.2f}});

    sprPlayerShootR.reserve(2);
    sprPlayerShootR.push_back({txSheetPang, {0.2f, 0.0f}, {0.4f, 0.2f}});
    sprPlayerShootR.push_back({txSheetPang, {0.4f, 0.0f}, {0.6f, 0.2f}});
    sprPlayerShootL.reserve(2);
    sprPlayerShootL.push_back({txSheetPang, {0.4f, 0.0f}, {0.2f, 0.2f}});
    sprPlayerShootL.push_back({txSheetPang, {0.6f, 0.0f}, {0.4f, 0.2f}});

    sprPlayerHitL = {txSheetPang, {0.2f, 0.2f}, {0.4f, 0.4f}};
    sprPlayerHitR = {txSheetPang, {0.4f, 0.2f}, {0.6f, 0.4f}};

    sprHook.reserve(2);
    sprHook.push_back({txSheetPang, {0.0f, 0.0f}, {0.1f, 1.0f}});
    sprHook.push_back({txSheetPang, {0.1f, 0.0f}, {0.2f, 1.0f}});

    sprSheetBee.reserve(8);
    sprSheetBee.push_back({txSheetBee, {0.000f, 0.0f}, {0.125f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.125f, 0.0f}, {0.250f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.250f, 0.0f}, {0.375f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.375f, 0.0f}, {0.500f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.500f, 0.0f}, {0.625f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.625f, 0.0f}, {0.750f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.750f, 0.0f}, {0.875f, 1.0f}});
    sprSheetBee.push_back({txSheetBee, {0.875f, 0.0f}, {1.000f, 1.0f}});

    sprBee = {txBee, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprLevel = {txLevel, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprTrees1 = {txTrees1, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprTrees2 = {txTrees2, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprCloud = {txClouds, {0.0f, 0.0f}, {1.0f, 1.0f}};

    sprSqr = {txColSqr, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprCrl = {txColCrl, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprBox = {txColBox, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprBall = {txColBall, {0.0f, 0.0f}, {1.0f, 1.0f}};

    sprMapPlayerIdle = {txPlayerIdle, {0.0f, 0.0f}, {1.0f, 1.0f}};
    sprMapPlayerRun.push_back({txPlayerRun, {0.000f, 0.0f}, {0.166f, 1.0f}});
    sprMapPlayerRun.push_back({txPlayerRun, {0.166f, 0.0f}, {0.333f, 1.0f}});
    sprMapPlayerRun.push_back({txPlayerRun, {0.333f, 0.0f}, {0.500f, 1.0f}});
    sprMapPlayerRun.push_back({txPlayerRun, {0.500f, 0.0f}, {0.666f, 1.0f}});
    sprMapPlayerRun.push_back({txPlayerRun, {0.666f, 0.0f}, {0.833f, 1.0f}});
    sprMapPlayerRun.push_back({txPlayerRun, {0.833f, 0.0f}, {1.000f, 1.0f}});
    sprMapGUI_06 = {txTileset, {0.625f, 0.00f}, {0.750f, 0.20f}};
    sprMapGUI_08 = {txTileset, {0.875f, 0.00f}, {1.000f, 0.20f}};
    sprMapGUI_09 = {txTileset, {0.000f, 0.20f}, {0.125f, 0.40f}};
    sprMapGUI_11 = {txTileset, {0.250f, 0.20f}, {0.375f, 0.40f}};
    sprMapGUI_16 = {txTileset, {0.875f, 0.20f}, {1.000f, 0.40f}};
    sprMapGUI_17 = {txTileset, {0.000f, 0.40f}, {0.125f, 0.60f}};
    sprMapGUI_18 = {txTileset, {0.125f, 0.40f}, {0.250f, 0.60f}};
    sprMapGUI_19 = {txTileset, {0.250f, 0.40f}, {0.375f, 0.60f}};
    sprMapGUI_29 = {txTileset, {0.500f, 0.60f}, {0.625f, 0.80f}};
}
