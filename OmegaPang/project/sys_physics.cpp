#include "sys_physics.h"

#include "game.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

struct Possible
{
    Box *a;
    Box *b;
};

static std::vector<Box> eachBox;       // Every Box box
static std::vector<Possible> posBox;   // Every Box pair that intersects
static std::vector<Collision> colBoxA; // Collision buffer
static std::vector<Collision> colBoxB; // Collision buffer

static std::vector<Collision> *colBox = &colBoxA;    // Confirmed collisions this frame
static std::vector<Collision> *colBoxOld = &colBoxB; // Confirmed collisions last frame

static const auto *const ptrSqrName = typeid(SquareCollider).name();
static const auto *const ptrCrlName = typeid(CircleCollider).name();
static const auto *const ptrPxlName = typeid(PixelCollider).name();

void SqrVsSqr(const Box &, const Box &);
void SqrVsCrl(const Box &, const Box &);
void CrlVsCrl(const Box &, const Box &);
void SqrVsPxl(const Box &, const Box &);
void CrlVsPxl(const Box &, const Box &);
void PxlVsPxl(const Box &, const Box &);

static constexpr auto Clamp = [](float v, float max, float min) { return v >= max ? max : (v <= min ? min : v); };

static const bool IsInColBox(const Collision &col)
{
    return std::find(colBox->begin(), colBox->end(), col) != colBox->end();
};

static const bool IsInColBoxOld(const Collision &col)
{
    return std::find(colBoxOld->begin(), colBoxOld->end(), col) != colBoxOld->end();
};

void SwapColBox()
{
    auto *temp = colBoxOld;
    colBoxOld = colBox;
    colBox = temp;
    colBox->clear();
}

SysPhysics::SysPhysics()
{
    eachBox.reserve(64);
    posBox.reserve(64);
    colBoxA.reserve(64);
    colBoxB.reserve(64);
}

void SysPhysics::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Reset buffers
    eachBox.clear();
    posBox.clear();
    SwapColBox();

    // Apply velocity
    auto rbView = reg.view<GameObject, Transform, RigidBody>();
    for (auto [entity, go, tf, rb] : rbView.each())
    {
        if (!go.isActive || !rb.enable)
            continue;

        tf.position += rb.velocity * (float)STP * 0.001f;
        rb.velocity = rb.velocity * (1.f - rb.linearDrag);
    }

    // Set views
    auto sqrView = reg.view<GameObject, Transform, SquareCollider>();
    auto crlView = reg.view<GameObject, Transform, CircleCollider>();
    auto pxlView = reg.view<GameObject, Transform, PixelCollider, SpriteRenderer>();

    // Get colliding entities
    for (auto [entity, go, tf, sc] : sqrView.each())
        if (go.isActive && sc.enable)
            eachBox.push_back({entity, tf.position + sc.center, sc.size, ptrSqrName});

    for (auto [entity, go, tf, cc] : crlView.each())
        if (go.isActive && cc.enable)
            eachBox.push_back({entity, tf.position + cc.center, {cc.radius, cc.radius}, ptrCrlName});

    for (auto [entity, go, tf, pc, sr] : pxlView.each())
        if (go.isActive && pc.enable && sr.enable && sr.sprite)
            eachBox.push_back({entity, tf.position, sr.size, ptrPxlName});

    // Set posible collisions
    Vec2 aMax, aMin, bMax, bMin;
    for (auto &&a : eachBox)
    {
        aMax = a.pos + a.size / 2.f;
        aMin = a.pos - a.size / 2.f;

        for (auto &&b : eachBox)
        {
            if (a.id == b.id)
                continue;

            bMax = b.pos + b.size / 2.f;
            bMin = b.pos - b.size / 2.f;

            if ((bMax.x > aMax.x && bMin.x > aMax.x) || (bMax.x < aMin.x && bMin.x < aMin.x) ||
                (bMax.y > aMax.y && bMin.y > aMax.y) || (bMax.y < aMin.y && bMin.y < aMin.y))
                continue;

            posBox.push_back({&a, &b});
        }
    }

    // Collide
    for (auto &&col : posBox)
    {
        if (col.a->type == ptrSqrName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsSqr(*col.a, *col.b);
            else if (col.b->type == ptrCrlName)
                SqrVsCrl(*col.a, *col.b);
            else if (col.b->type == ptrPxlName)
                SqrVsPxl(*col.a, *col.b);
        }
        else if (col.a->type == ptrCrlName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsCrl(*col.b, *col.a);
            else if (col.b->type == ptrCrlName)
                CrlVsCrl(*col.a, *col.b);
            else if (col.b->type == ptrPxlName)
                CrlVsPxl(*col.a, *col.b);
        }
        else if (col.a->type == ptrPxlName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsPxl(*col.b, *col.a);
            else if (col.b->type == ptrCrlName)
                CrlVsPxl(*col.b, *col.a);
            else if (col.b->type == ptrPxlName)
                PxlVsPxl(*col.b, *col.a);
        }
    }

    // Exit callbacks
    for (auto &&col : *colBoxOld)
        if (IsInColBox(col))
        {
            if (col.a.type == ptrSqrName)
                reg.get<SquareCollider>(col.a.id).OnTriggerStay(&col);
            else if (col.a.type == ptrCrlName)
                reg.get<CircleCollider>(col.a.id).OnTriggerStay(&col);
            else if (col.a.type == ptrPxlName)
                reg.get<PixelCollider>(col.a.id).OnTriggerStay(&col);
        }
        else
        {
            if (col.a.type == ptrSqrName)
                reg.get<SquareCollider>(col.a.id).OnTriggerExit(&col);
            else if (col.a.type == ptrCrlName)
                reg.get<CircleCollider>(col.a.id).OnTriggerExit(&col);
            else if (col.a.type == ptrPxlName)
                reg.get<PixelCollider>(col.a.id).OnTriggerExit(&col);
        }
}

void SqrVsSqr(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    Collision col = {a, b};
    colBox->push_back(col);

    // Callbacks
    if (!IsInColBoxOld(col))
        reg.get<SquareCollider>(a.id).OnTriggerEnter(&col);
}

void SqrVsCrl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    Vec2 point = {0.f, 0.f};

    auto maxX = a.pos.x + a.size.x / 2.f;
    auto minX = a.pos.x - a.size.x / 2.f;

    auto maxY = a.pos.y + a.size.y / 2.f;
    auto minY = a.pos.y - a.size.y / 2.f;

    point.x = Clamp(b.pos.x, maxX, minX);
    point.y = Clamp(b.pos.x, maxY, minY);

    auto distance = (point - b.pos.x).Magnitude();
    auto isColliding = distance < b.size.x / 2.f;

    if (isColliding)
        return;

    // Save collision
    Collision col = {a, b};
    colBox->push_back(col);

    // Callbacks
    if (!IsInColBoxOld(col))
        reg.get<SquareCollider>(a.id).OnTriggerEnter(&col);
}

void CrlVsCrl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    Vec2 point = {0.f, 0.f};
    auto isColliding = Vec2::Distance(a.pos, b.pos) < a.size.x + b.size.x;

    if (isColliding)
        return;

    // Save collision
    Collision col = {a, b};
    colBox->push_back(col);

    // Callbacks
    if (!IsInColBoxOld(col))
        reg.get<SquareCollider>(a.id).OnTriggerEnter(&col);
    else
        reg.get<SquareCollider>(a.id).OnTriggerStay(&col);
}

void SqrVsPxl(const Box &a, const Box &b)
{
}

void CrlVsPxl(const Box &a, const Box &b)
{
}

void PxlVsPxl(const Box &a, const Box &b)
{
}
