#pragma once

class FontLoader {
  friend class Engine;

private:                                   // SINGLETON
  FontLoader();                            //
  static FontLoader instance;              //
public:                                    //
  FontLoader(const FontLoader &) = delete; //

public:
  // static stbi_uc* pixels;
  // static ltex_t* texture;
  // static Sprite sprPlayer;
  // static Sprite sprEnemy;
  // static Sprite sprBullet;
  // static Sprite sprFloor01;
  // static Sprite sprFloor02;
  // static Sprite sprFloor03;
  // static Sprite sprFloor04;

  static void LoadFonts();
};
