#include "sprite_loader.h"

#include "engine_render.h"
#include "litegfx.h"
#include "stb_image.h"

static const char *file = "resources/sprSheet.png";
static stbi_uc *pixels = nullptr;
static ltex_t *texture = nullptr;

Sprite SpriteLoader::sprPlayer = {};
Sprite SpriteLoader::sprEnemy = {};
Sprite SpriteLoader::sprBullet = {};
Sprite SpriteLoader::sprFloor01 = {};
Sprite SpriteLoader::sprFloor02 = {};
Sprite SpriteLoader::sprFloor03 = {};
Sprite SpriteLoader::sprFloor04 = {};

SpriteLoader SpriteLoader::instance;

SpriteLoader::SpriteLoader() {}

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

  // Sprites
  sprPlayer = {texture, {0.f, 0.f}, {0.25f, 0.5f}};
  sprEnemy = {texture, {0.25f, 0.f}, {0.5f, 0.5f}};
  sprBullet = {texture, {0.5f, 0.f}, {0.75f, 0.5f}};
  sprFloor01 = {texture, {0.0f, 0.5f}, {0.25f, 1.0f}};
  sprFloor02 = {texture, {0.25f, 0.5f}, {0.5f, 1.0f}};
  sprFloor03 = {texture, {0.5f, 0.5f}, {0.75f, 1.0f}};
  sprFloor04 = {texture, {0.75f, 0.5f}, {1.f, 1.0f}};
}
