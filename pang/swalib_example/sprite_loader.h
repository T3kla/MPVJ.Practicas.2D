#pragma once

#include <vector>

#include "sprite.h"

class SpriteLoader {

private:                                       // SINGLETON
  SpriteLoader();                              //
  static SpriteLoader instance;                //
public:                                        //
  SpriteLoader(const SpriteLoader &) = delete; //

private:
  static unsigned int txBg;
  static unsigned int txSheet;
  static unsigned int txSheetRev;

public:
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

  static void LoadTextures();
  static void UnloadTextures();
};
