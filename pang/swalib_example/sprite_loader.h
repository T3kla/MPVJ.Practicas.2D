#pragma once

#include "litegfx.h"
#include "sprite.h"
#include "stb_image.h"

#include <vector>

class SpriteLoader
{
    static SpriteLoader Instance;

  private:
    static stbi_uc *pixels;
    static ltex_t *txBg;
    static ltex_t *txSheet;
    static ltex_t *txSheetRev;

  public:
    SpriteLoader() = default;
    SpriteLoader(const SpriteLoader &) = delete;

    static void LoadTextures();
    static void UnloadTextures();

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
};
