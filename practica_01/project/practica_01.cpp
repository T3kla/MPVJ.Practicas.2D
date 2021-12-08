#include "practica_01.h"
#include "engine.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "stasis.h"
#include "vec.h"

static const unsigned int titleLength = 256;
static char title[titleLength];
static Vec2 rot = {1.f, 0.f};
static float dis = 100.f;

P01::P01()
{
    Game::Subscribe(this);
}

P01::~P01()
{
    Game::UnSubscribe(this);
}

void P01::Start()
{
    Input::SetTitle(title);
}

void P01::Update()
{
    int w, h;
    Render::GetWindowSize(w, h);
    auto screenCenter = Vec2((float)w / 2.f, (float)h / 2.f);
    auto mousePos = Engine::GetMousePos();

    // Rect in the middle of the screen
    rect1.SetPos(screenCenter);

    // Rect following the mouse
    rect2.SetPos(mousePos);

    // Oval rotating around rect2
    rot = Vec2::RotateAround(32.f * (float)Stasis::GetDelta() * 0.001f, rot, Vec2::Zero());
    // auto rot = Vec2::RotateAround(360. * Stasis::GetDelta() * 0.001, rect3.GetPos() - rect2.GetPos(),
    // Vec2::Zero()).Normalized(); // Diversion
    oval1.SetPos(rot * dis + rect2.GetPos());

    // Title
    auto scr2mouse = (mousePos - screenCenter).Magnitude();
    auto rect3ang = rot.AngleDeg();
    snprintf(title, titleLength, "Mouse to center: %.0fpx   Oval at angle: %.0fdeg", scr2mouse, rect3ang);
}

void P01::Fixed()
{
}

void P01::End()
{
}
