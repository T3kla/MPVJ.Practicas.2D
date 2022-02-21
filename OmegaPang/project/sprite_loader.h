#pragma once

#include "litegfx.h"
#include "sprite.h"
#include "stb_image.h"

#include <vector>

class FileLoader;

class SpriteLoader
{
    friend FileLoader;
    static SpriteLoader Instance;
    static std::vector<ltex_t *> Textures;

    static void InitBuffers();
    static void ClearBuffers();

  private:
    SpriteLoader() = default;
    SpriteLoader(const SpriteLoader &) = delete;

  public:
    static void LoadTexture(const char *name, const char *file);
    static ltex_t *GetTexture(const char *name);

    static void UnloadTextures();

    static void SetSprites();

    // Bg
    static Sprite sprBg;

    // Balls
    static std::vector<Sprite> sprBalls;
    static std::vector<Sprite> sprExpls;

    // Player
    static Sprite sprPlayerIdle;
    static std::vector<Sprite> sprPlayerMoveL;
    static std::vector<Sprite> sprPlayerMoveR;
    static std::vector<Sprite> sprPlayerShootL;
    static std::vector<Sprite> sprPlayerShootR;
    static Sprite sprPlayerHitL;
    static Sprite sprPlayerHitR;

    // Hook
    static std::vector<Sprite> sprHook;

    // Bee
    static std::vector<Sprite> sprBee;
};
