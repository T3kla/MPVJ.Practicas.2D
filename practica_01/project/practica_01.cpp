#include "practica_01.h"
#include "engine.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "stasis.h"
#include "vec.h"

P01::P01() { Game::Subscribe(this); }
P01::~P01() { Game::UnSubscribe(this); }

void P01::Start() {
  // Set Background Dark Grey
  Render::SetBgColor({0.1f, 0.1f, 0.1f, 1.f});

  // Set Title
  Input::SetTitle(title);
}

// Update runs each tick, gotta use Stasis::GetDelta()
// Fixed runs at 144fps, gotta use Engine::STEP

// Both can run simultaneusly, demonstrating that the time
// system remains deterministic

void P01::Update() {
  // int w, h;
  // Render::GetWindowSize(w, h);
  // auto screenCenter = Vec2((float)w / 2.f, (float)h / 2.f);
  // auto mousePos = Engine::GetMousePos();

  //// Rect1 in the middle of the screen
  // rect1.SetPos(screenCenter);

  //// Rect2 following the mouse
  // rect2.SetPos(mousePos);

  //// Oval1 rotating counterclockwise around rect2
  // auto ang1 = 32.f * (float)Stasis::GetDelta() * 0.001f;
  // rot1 = Vec2::RotateAround(ang1, rot1, Vec2::Zero());
  // oval1.SetPos(rot1 * dis + rect2.GetPos());

  //// Oval2 rotating clockwise around rect2 (for fun)
  // auto ang2 = -32.f * (float)Stasis::GetDelta() * 0.001f;
  // auto rot2 =
  //     Vec2::RotateAround(ang2, oval2.GetPos() - rect2.GetPos(), Vec2::Zero())
  //         .Normalized();
  // oval2.SetPos(rot2 * dis + rect2.GetPos());

  //// Title
  // auto scr2mouse = (mousePos - screenCenter).Magnitude();
  // auto rect3ang = rot1.AngleDeg();
  // snprintf(title, TITLE_LEN, "Mouse to center: %.0fpx   Oval at angle:
  // %.0fdeg",
  //          scr2mouse, rect3ang);
}

void P01::Fixed() {
  int w, h;
  Render::GetWindowSize(w, h);
  auto screenCenter = Vec2((float)w / 2.f, (float)h / 2.f);
  auto mousePos = Engine::GetMousePos();

  // Rect1 in the middle of the screen
  rect1.SetPos(screenCenter);

  // Rect2 following the mouse
  rect2.SetPos(mousePos);

  // Oval1 rotating counterclockwise around rect2
  auto ang1 = 32.f * (float)STEP * 0.001f;
  rot1 = Vec2::RotateAround(ang1, rot1, Vec2::Zero());
  oval1.SetPos(rot1 * dis + rect2.GetPos());

  // Oval2 rotating clockwise around rect2 (for fun)
  auto ang2 = -32.f * (float)STEP * 0.001f;
  auto rot2 =
      Vec2::RotateAround(ang2, oval2.GetPos() - rect2.GetPos(), Vec2::Zero())
          .Normalized();
  oval2.SetPos(rot2 * dis + rect2.GetPos());

  // Title
  auto scr2mouse = (mousePos - screenCenter).Magnitude();
  auto rect3ang = rot1.AngleDeg();
  snprintf(title, TITLE_LEN, "Mouse to center: %.0fpx   Oval at angle: %.0fdeg",
           scr2mouse, rect3ang);
}

void P01::End() {}
