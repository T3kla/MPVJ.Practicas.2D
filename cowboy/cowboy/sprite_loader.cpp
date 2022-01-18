#include "sprite_loader.h"
#include "engine_render.h"

static const char *file = "resources/sprSheet.png";

stbi_uc *SpriteLoader::pixels = nullptr;
ltex_t *SpriteLoader::texture = nullptr;
Sprite SpriteLoader::sprPlayer = {};
Sprite SpriteLoader::sprEnemy = {};
Sprite SpriteLoader::sprBullet = {};
Sprite SpriteLoader::sprFloor01 = {};
Sprite SpriteLoader::sprFloor02 = {};
Sprite SpriteLoader::sprFloor03 = {};
Sprite SpriteLoader::sprFloor04 = {};

SpriteLoader SpriteLoader::instance;

SpriteLoader::SpriteLoader() {}

SpriteLoader &SpriteLoader::Get() { return instance; }

void SpriteLoader::LoadSprites() {
  // Set Background Black
  EngineRender::SetBgColor({0.5f, 0.44f, 0.37f, 1.f});

  // SpriteSheet Loading
  int w, h, c;
  pixels = stbi_load(file, &w, &h, &c, 4);
  if (!pixels)
    throw "Error loading image";

  // Texture Allocation
  texture = ltex_alloc(w, h, 0);

  // Texture Dump
  ltex_setpixels(texture, pixels);

  // Player Sprite
  sprPlayer.texture = texture;
  sprPlayer.uv0 = {0.f, 0.f};
  sprPlayer.uv1 = {0.25f, 0.5f};

  // Enemy Sprite
  sprEnemy.texture = texture;
  sprEnemy.uv0 = {0.25f, 0.f};
  sprEnemy.uv1 = {0.5f, 0.5f};

  // Bullet Sprite
  sprBullet.texture = texture;
  sprBullet.uv0 = {0.5f, 0.f};
  sprBullet.uv1 = {0.75f, 0.5f};

  // Floor Sprites
  sprFloor01.texture = texture;
  sprFloor01.uv0 = {0.0f, 0.5f};
  sprFloor01.uv1 = {0.25f, 1.0f};

  sprFloor02.texture = texture;
  sprFloor02.uv0 = {0.25f, 0.5f};
  sprFloor02.uv1 = {0.5f, 1.0f};

  sprFloor03.texture = texture;
  sprFloor03.uv0 = {0.5f, 0.5f};
  sprFloor03.uv1 = {0.75f, 1.0f};

  sprFloor04.texture = texture;
  sprFloor04.uv0 = {0.75f, 0.5f};
  sprFloor04.uv1 = {1.f, 1.0f};
}
