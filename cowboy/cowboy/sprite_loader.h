#pragma once

#include "litegfx.h"
#include "sprite.h"
#include "stb_image.h"

class SpriteLoader {
  friend class Engine;

private:                                       // SINGLETON
  SpriteLoader();                              //
  static SpriteLoader instance;                //
public:                                        //
  SpriteLoader(const SpriteLoader &) = delete; //
  static SpriteLoader &Get();                  //

public:
  static stbi_uc *pixels;
  static ltex_t *texture;
  static Sprite sprPlayer;
  static Sprite sprEnemy;
  static Sprite sprBullet;
  static Sprite sprFloor01;
  static Sprite sprFloor02;
  static Sprite sprFloor03;
  static Sprite sprFloor04;

  static void LoadSprites(); // TODO: load into arrays per animation
};
