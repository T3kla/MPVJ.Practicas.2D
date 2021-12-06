#include "practica_01.h"

#include "game.h"
#include "rect.h"

P01::P01()
{
    Game::Subscribe(this);
}

P01::~P01()
{
    Game::UnSubscribe(this);
}

auto r1dir = true;
auto r2dir = true;
auto vel = 0.5f;

void P01::Update(const double &dt)
{
    auto pos = rect1.GetPos();

    if (pos.x < 100.f)
        r1dir = true;
    if (pos.x > 600.f)
        r1dir = false;

    auto speed = r1dir ? vel : -vel;

    rect1.SetPos(vec2(pos.x + speed * dt, pos.y));
}

void P01::Fixed(const double &dt)
{
    auto pos = rect2.GetPos();

    if (pos.x < 100.f)
        r2dir = true;
    if (pos.x > 600.f)
        r2dir = false;

    auto speed = r2dir ? vel : -vel;

    rect2.SetPos(vec2(pos.x + speed * dt, pos.y));
}
