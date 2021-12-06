#include "practica_01.h"

#include "game.h"
#include "rect.h"
#include "render.h"
#include "vec.h"

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
}

void P01::Update(const double &dt)
{
    int w, h;
    Render::GetWindowSize(w, h);
    rect1.SetPos(Vec2((float)w / 2.f, (float)h / 2.f));
}

void P01::Fixed(const double &dt)
{
}

void P01::End()
{
}
