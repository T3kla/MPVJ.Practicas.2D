#pragma once

#include "sprite.h"

class SpriteLoader {
  friend class Engine;

private:                                       // SINGLETON
  SpriteLoader();                              //
  static SpriteLoader instance;                //
public:                                        //
  SpriteLoader(const SpriteLoader &) = delete; //

public:
  static Sprite sprPlayer;
  static Sprite sprEnemy;
  static Sprite sprBullet;
  static Sprite sprFloor01;
  static Sprite sprFloor02;
  static Sprite sprFloor03;
  static Sprite sprFloor04;

  static void LoadSprites();
};
