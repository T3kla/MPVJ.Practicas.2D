#pragma once

#include "sprite.h"
#include "texture.h"

#include <vector>

class SpriteLoader
{
    friend class AssetLoader;

    static SpriteLoader Instance;
    static std::vector<Texture> Textures;

  private:
    SpriteLoader() = default;
    SpriteLoader(const SpriteLoader &) = delete;

    static void LoadTexture(const char *name, const char *file);
    static void UnloadTextures();

    static void SetSprites();

  public:
    static Texture *GetTexture(const char *name);

    // ***** Sprite accessors *****
    static Sprite sprBg;
    static std::vector<Sprite> sprBalls;
    static std::vector<Sprite> sprExpls;
    static Sprite sprPlayerIdle;
    static std::vector<Sprite> sprPlayerMoveL;
    static std::vector<Sprite> sprPlayerMoveR;
    static std::vector<Sprite> sprPlayerShootL;
    static std::vector<Sprite> sprPlayerShootR;
    static Sprite sprPlayerHitL;
    static Sprite sprPlayerHitR;
    static std::vector<Sprite> sprHook;

    // Bee
    static std::vector<Sprite> sprSheetBee;
    static Sprite sprBee;
    static Sprite sprLevel;
    static Sprite sprTrees1;
    static Sprite sprTrees2;
    static Sprite sprCloud;

    // Collisions
    static Sprite sprSqr;
    static Sprite sprCrl;
    static Sprite sprBox;
    static Sprite sprBall;
};
