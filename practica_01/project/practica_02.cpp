#include "practica_02.h"
#include "engine.h"
#include "game.h"
#include "render.h"

static const char *file = "resources/sprSheet.png";

P02::P02() { Game::Subscribe(this); }
P02::~P02() { Game::UnSubscribe(this); }

void P02::Start() {
  // Set Background Black
  Render::SetBgColor({0.f, 0.f, 0.f, 1.f});

  // SpriteSheet Loading
  int w, h, c;
  pixels = stbi_load(file, &w, &h, &c, 4);
  if (!pixels)
    throw "Error loading image";

  // Texture Allocation
  texture = ltex_alloc(256, 64, 0);

  // Texture Dump
  ltex_setpixels(texture, pixels);

  // Sprite Creation
  wall.reserve(16);
  for (size_t x = 0; x < 4; x++)
    for (size_t y = 0; y < 4; y++) {
      wall.emplace_back(new Sprite(
          texture, {defSize / 2.f + defSize * x, defSize / 2.f + defSize * y},
          {defSize, defSize}, {0.25f, 0.f}, {0.5f, 1.f}, BLEND_SOLID));
    }

  light = new Sprite{texture,     {0.f, 0.f},   {5000.f, 5000.f},
                     {0.5f, 0.f}, {0.75f, 1.f}, BLEND_MUL};

  torch = new Sprite{texture,      {0.f, 0.f}, {400.f, 400.f},
                     {0.75f, 0.f}, {1.f, 1.f}, BLEND_ALPHA};

  fence.reserve(16);
  for (size_t x = 0; x < 4; x++)
    for (size_t y = 0; y < 4; y++) {
      fence.emplace_back(new Sprite(
          texture, {defSize / 2.f + defSize * x, defSize / 2.f + defSize * y},
          {defSize, defSize}, {0.f, 0.f}, {0.25f, 1.f}, BLEND_ALPHA));
    }
}

void P02::Update() {}

void P02::Fixed() {
  auto mousePos = Engine::GetMousePos();
  Vec2 offset(-60.f, -80.f);
  torch->SetPos(mousePos + offset);
  light->SetPos(mousePos + offset);
}

void P02::End() {
  // SpriteSheet Unloading
  if (pixels)
    stbi_image_free(pixels);

  // Texture Deallocation
  ltex_free(texture);

  // Sprite Deallocation
  delete torch;
  delete light;

  for (size_t i = 0; i < wall.size(); i++)
    delete wall[i];
  wall.clear();

  for (size_t i = 0; i < fence.size(); i++)
    delete fence[i];
  fence.clear();
}
