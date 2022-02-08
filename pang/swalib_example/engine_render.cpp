#include "engine_render.h"

#include "engine.h"
#include "stasis.h"

#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"

#include "gameobject.h"
#include "sprite.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "sys_player.h"

#include "scene_01.h"

#include <algorithm>
#include <vector>

static char buffer[256];
static float w = 0;
static float h = 0;

static std::vector<Entity *> layered;

EngineRender EngineRender::instance;
EngineRender::EngineRender() {}
EngineRender &EngineRender::Get() { return instance; }

void EngineRender::Awake() {
  FONT_Init();

  // Save screen size as float
  w = (float)SCR_WIDTH;
  h = (float)SCR_HEIGHT;

  // Set up rendering.
  //    Sets up clipping.
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  //    Specifies clear values for the color buffers.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  //    Specifies projection matrix is the current matrix.
  glMatrixMode(GL_PROJECTION);
  //    Replaces the current matrix with the identity matrix.
  glLoadIdentity();
  //    Multiplies the current matrix by an orthographic matrix.
  glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  //    Enabling two-dimensional texturing.
  glEnable(GL_TEXTURE_2D);

  // NOTA: Mirar diferencias comentando las 2 siguientes funciones.
  //    Blend the incoming RGBA color values with the values in
  //    the color buffers.
  glEnable(GL_BLEND);
  //	Blend func. for alpha color.
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Load textures
  SpriteLoader::LoadTextures();

  // Layers buffer
  layered.reserve(10);
}

void EngineRender::Start() {}

void EngineRender::Update() {}

void EngineRender::Fixed() {
  // Render
  glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

  // Render background
  CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f),
                            vec2(1280.f, 720.f), SpriteLoader::sprBg.texture);

  // Layered rendering preparation
  layered.clear();

  for (auto &entity : Scene_01::GetRegistry()) {
    auto *go = entity->GetComponent<GameObject>();
    auto *sr = entity->GetComponent<SpriteRenderer>();

    if (go && sr && go->isActive)
      layered.push_back(entity);
  }

  std::sort(layered.begin(), layered.end(), [](Entity *a, Entity *b) {
    auto *aSR = a->GetComponent<SpriteRenderer>();
    auto *bSR = b->GetComponent<SpriteRenderer>();
    return aSR->layer < bSR->layer;
  });

  // Render stuff
  for (auto &entity : layered) {
    auto *tf = entity->GetComponent<Transform>();
    auto *go = entity->GetComponent<GameObject>();
    auto *sr = entity->GetComponent<SpriteRenderer>();
    auto *sa = entity->GetComponent<SpriteAnimation>();

    if (!tf || !go || !sr || !go->isActive)
      continue;

    // Animations
    if (sa && sa->enable && sa->animation) {
      sa->count += (float)STP * 0.001f;

      if (sa->count >= sa->duration)
        sa->count = fmodf(sa->count, sa->duration);

      auto frameFreq = sa->duration / sa->animation->size();
      auto frame = (int)floorf(sa->count / frameFreq);

      sr->sprite = &sa->animation->at(frame);
    }

    // Sprite drawing
    if (sr && sr->enable) {
      auto &pos = tf->position + sr->offsetPosition;
      auto &sze = sr->size;
      auto &uv0 = sr->sprite->uv0;
      auto &uv1 = sr->sprite->uv1;
      CORE_RenderCenteredSpriteWithUVs(vec2(pos.x, pos.y), vec2(sze.x, sze.y),
                                       vec2(uv0.x, uv0.y), vec2(uv1.x, uv1.y),
                                       sr->sprite->texture);
    }
  }

  // Render FPS and stuff
  sprintf(buffer, "TIME: %0.1f", Stasis::GetTimeScaled() / 1000.);
  FONT_DrawString({w * 0.05f, h * 0.9f}, buffer);
  sprintf(buffer, "HEALTH: %d", SysPlayer::GetPlayerHealth());
  FONT_DrawString({w * 0.8f, h * 0.9f}, buffer);

  SYS_Show(); // Exchanges the front and back buffers}
}

void EngineRender::Quit() { FONT_End(); }
