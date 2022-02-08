#include "sprite_loader.h"

#include "core.h"

unsigned int SpriteLoader::txBg = 0;
unsigned int SpriteLoader::txSheet = 0;
unsigned int SpriteLoader::txSheetRev = 0;

Sprite SpriteLoader::sprBg;

std::vector<Sprite> SpriteLoader::sprBalls;
std::vector<Sprite> SpriteLoader::sprExpls;

Sprite SpriteLoader::sprPlayerIdle;
std::vector<Sprite> SpriteLoader::sprPlayerMoveL;
std::vector<Sprite> SpriteLoader::sprPlayerMoveR;
std::vector<Sprite> SpriteLoader::sprPlayerShootL;
std::vector<Sprite> SpriteLoader::sprPlayerShootR;
Sprite SpriteLoader::sprPlayerHitL;
Sprite SpriteLoader::sprPlayerHitR;

std::vector<Sprite> SpriteLoader::sprHook;

SpriteLoader SpriteLoader::instance;
SpriteLoader::SpriteLoader() {}

void SpriteLoader::LoadTextures() {
  txBg = CORE_LoadPNG("data/txBG.png", true);
  txSheet = CORE_LoadPNG("data/sprSheet.png", false);
  txSheetRev = CORE_LoadPNG("data/sprSheet.png", false, true);

  sprBg = {txBg, Vec2::Zero(), Vec2::One()};

  sprBalls.push_back({txSheet, {0.2f, 0.6f}, {0.6f, 1.0f}});
  sprBalls.push_back({txSheet, {0.2f, 0.4f}, {0.4f, 0.6f}});
  sprBalls.push_back({txSheet, {0.6f, 0.4f}, {0.8f, 0.6f}});
  sprBalls.push_back({txSheet, {0.6f, 0.2f}, {0.8f, 0.4f}});

  sprExpls.push_back({txSheet, {0.6f, 0.6f}, {1.0f, 1.0f}});
  sprExpls.push_back({txSheet, {0.4f, 0.4f}, {0.6f, 0.6f}});
  sprExpls.push_back({txSheet, {0.8f, 0.4f}, {1.0f, 0.6f}});
  sprExpls.push_back({txSheet, {0.8f, 0.2f}, {1.0f, 0.4f}});

  sprPlayerIdle = {txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}};

  sprPlayerMoveL.push_back({txSheetRev, {0.2f, 0.0f}, {0.4f, 0.2f}});
  sprPlayerMoveL.push_back({txSheetRev, {0.0f, 0.0f}, {0.2f, 0.2f}});

  sprPlayerShootL.push_back({txSheetRev, {0.6f, 0.0f}, {0.8f, 0.2f}});
  sprPlayerShootL.push_back({txSheetRev, {0.4f, 0.0f}, {0.6f, 0.2f}});

  sprPlayerMoveR.push_back({txSheet, {0.6f, 0.0f}, {0.8f, 0.2f}});
  sprPlayerMoveR.push_back({txSheet, {0.8f, 0.0f}, {1.0f, 0.2f}});

  sprPlayerShootR.push_back({txSheet, {0.2f, 0.0f}, {0.4f, 0.2f}});
  sprPlayerShootR.push_back({txSheet, {0.4f, 0.0f}, {0.6f, 0.2f}});

  sprPlayerHitL = {txSheet, {0.2f, 0.2f}, {0.4f, 0.4f}};
  sprPlayerHitR = {txSheet, {0.4f, 0.2f}, {0.6f, 0.4f}};

  sprHook.push_back({txSheet, {0.0f, 0.0f}, {0.1f, 1.0f}});
  sprHook.push_back({txSheet, {0.1f, 0.0f}, {0.2f, 1.0f}});
}

void SpriteLoader::UnloadTextures() {
  CORE_UnloadPNG(txBg);
  CORE_UnloadPNG(txSheet);
  CORE_UnloadPNG(txSheetRev);
}
