#include "sprite_loader.h"

#include "stb_image.h"
#include "texture.h"

Sprite SpriteLoader::sprBg;
Sprite SpriteLoader::sprPlayerIdle;
Sprite SpriteLoader::sprPlayerHitL;
Sprite SpriteLoader::sprPlayerHitR;
Sprite SpriteLoader::sprBox;
std::vector<Sprite> SpriteLoader::sprBalls;
std::vector<Sprite> SpriteLoader::sprExpls;
std::vector<Sprite> SpriteLoader::sprPlayerMoveL;
std::vector<Sprite> SpriteLoader::sprPlayerMoveR;
std::vector<Sprite> SpriteLoader::sprPlayerShootL;
std::vector<Sprite> SpriteLoader::sprPlayerShootR;
std::vector<Sprite> SpriteLoader::sprHook;
std::vector<Sprite> SpriteLoader::sprBee;

SpriteLoader SpriteLoader::Instance;
std::vector<Texture> SpriteLoader::Textures;

void Load(const char *file, ltex_t *&texture)
{
    int w, h, c;

    stbi_uc *pixels;

    pixels = stbi_load(file, &w, &h, &c, 4);

    if (!pixels)
        throw "Error loading image";

    texture = ltex_alloc(w, h, 0);
    ltex_setpixels(texture, pixels);
    stbi_image_free(pixels);
}

void SpriteLoader::LoadTexture(const char *name, const char *file)
{
    ltex_t *tx = nullptr;

    Load(file, tx);

    Textures.push_back({name, tx});
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
    auto *txBg = GetTexture("txBG.png")->texture;
    auto *txSheet = GetTexture("sprSheet.png")->texture;
    auto *txBee = GetTexture("sprBee.png")->texture;
    auto *txBox = GetTexture("box.png")->texture;

    // Sprite mapping
    sprBg = {txBg, Vec2::Zero(), Vec2::One()};

    sprBalls.reserve(4);
    sprBalls.push_back({txSheet, {0.2f, 0.6f}, {0.6f, 1.0f}});
    sprBalls.push_back({txSheet, {0.2f, 0.4f}, {0.4f, 0.6f}});
    sprBalls.push_back({txSheet, {0.6f, 0.4f}, {0.8f, 0.6f}});
    sprBalls.push_back({txSheet, {0.6f, 0.2f}, {0.8f, 0.4f}});

    sprExpls.reserve(4);
    sprExpls.push_back({txSheet, {0.6f, 0.6f}, {1.0f, 1.0f}});
    sprExpls.push_back({txSheet, {0.4f, 0.4f}, {0.6f, 0.6f}});
    sprExpls.push_back({txSheet, {0.8f, 0.4f}, {1.0f, 0.6f}});
    sprExpls.push_back({txSheet, {0.8f, 0.2f}, {1.0f, 0.4f}});

    sprPlayerIdle = {txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}};

    sprPlayerMoveR.reserve(2);
    sprPlayerMoveR.push_back({txSheet, {0.6f, 0.0f}, {0.8f, 0.2f}});
    sprPlayerMoveR.push_back({txSheet, {0.8f, 0.0f}, {1.0f, 0.2f}});
    sprPlayerMoveL.reserve(2);
    sprPlayerMoveL.push_back({txSheet, {0.8f, 0.0f}, {0.6f, 0.2f}});
    sprPlayerMoveL.push_back({txSheet, {1.0f, 0.0f}, {0.8f, 0.2f}});

    sprPlayerShootR.reserve(2);
    sprPlayerShootR.push_back({txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}});
    sprPlayerShootR.push_back({txSheet, {0.4f, 0.0f}, {0.6f, 0.2f}});
    sprPlayerShootL.reserve(2);
    sprPlayerShootL.push_back({txSheet, {0.4f, 0.0f}, {0.2f, 0.2f}});
    sprPlayerShootL.push_back({txSheet, {0.6f, 0.0f}, {0.4f, 0.2f}});

    sprPlayerHitL = {txSheet, {0.2f, 0.2f}, {0.4f, 0.4f}};
    sprPlayerHitR = {txSheet, {0.4f, 0.2f}, {0.6f, 0.4f}};

    sprHook.reserve(2);
    sprHook.push_back({txSheet, {0.0f, 0.0f}, {0.1f, 1.0f}});
    sprHook.push_back({txSheet, {0.1f, 0.0f}, {0.2f, 1.0f}});

    sprBee.reserve(8);
    sprBee.push_back({txBee, {0.000f, 0.0f}, {0.125f, 1.0f}});
    sprBee.push_back({txBee, {0.125f, 0.0f}, {0.250f, 1.0f}});
    sprBee.push_back({txBee, {0.250f, 0.0f}, {0.375f, 1.0f}});
    sprBee.push_back({txBee, {0.375f, 0.0f}, {0.500f, 1.0f}});
    sprBee.push_back({txBee, {0.500f, 0.0f}, {0.625f, 1.0f}});
    sprBee.push_back({txBee, {0.625f, 0.0f}, {0.750f, 1.0f}});
    sprBee.push_back({txBee, {0.750f, 0.0f}, {0.875f, 1.0f}});
    sprBee.push_back({txBee, {0.875f, 0.0f}, {1.000f, 1.0f}});

    sprBox = {txBox, {0.0f, 0.0f}, {1.0f, 1.0f}};
}
