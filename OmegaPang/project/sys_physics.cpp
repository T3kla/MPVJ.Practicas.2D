#include "sys_physics.h"

#include "litegfx.h"

#include "game.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite.h"
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
void SqrVsCrl(const Box &, const Box &, bool);
void CrlVsCrl(const Box &, const Box &);
void SqrVsPxl(const Box &, const Box &, bool);
void CrlVsPxl(const Box &, const Box &, bool);
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
            eachBox.push_back({entity, tf.position + sc.center, Vec2::Hadamard(sc.size, tf.scale), ptrSqrName});

    for (auto [entity, go, tf, cc] : crlView.each())
        if (go.isActive && cc.enable)
            eachBox.push_back(
                {entity, tf.position + cc.center, Vec2::Hadamard({cc.radius, cc.radius}, tf.scale), ptrCrlName});

    for (auto [entity, go, tf, pc, sr] : pxlView.each())
        if (go.isActive && pc.enable && sr.enable && sr.sprite)
            eachBox.push_back({entity, tf.position, Vec2::Hadamard(sr.size, tf.scale), ptrPxlName});

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
    // Collision bufferCol = {};
    for (auto &&col : posBox)
    {
        // bufferCol = {*col.b, *col.a};
        // if (std::find(colBox->begin(), colBox->end(), bufferCol) != colBox->end())
        //     continue;

        if (col.a->type == ptrSqrName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsSqr(*col.a, *col.b);
            else if (col.b->type == ptrCrlName)
                SqrVsCrl(*col.a, *col.b, true);
            else if (col.b->type == ptrPxlName)
                SqrVsPxl(*col.a, *col.b, true);
        }
        else if (col.a->type == ptrCrlName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsCrl(*col.b, *col.a, false);
            else if (col.b->type == ptrCrlName)
                CrlVsCrl(*col.a, *col.b);
            else if (col.b->type == ptrPxlName)
                CrlVsPxl(*col.a, *col.b, true);
        }
        else if (col.a->type == ptrPxlName)
        {
            if (col.b->type == ptrSqrName)
                SqrVsPxl(*col.b, *col.a, false);
            else if (col.b->type == ptrCrlName)
                CrlVsPxl(*col.b, *col.a, false);
            else if (col.b->type == ptrPxlName)
                PxlVsPxl(*col.b, *col.a);
        }
    }

    // Exit callbacks
    for (auto &&col : *colBoxOld)
        if (reg.valid(col.a.id))
            if (col.a.type == ptrSqrName)
            {
                auto *sc = reg.try_get<SquareCollider>(col.a.id);
                if (sc)
                    if (IsInColBox(col))
                        sc->OnTriggerStay(&col);
                    else
                        sc->OnTriggerExit(&col);
            }
            else if (col.a.type == ptrCrlName)
            {
                auto *cc = reg.try_get<CircleCollider>(col.a.id);
                if (cc)
                    if (IsInColBox(col))
                        cc->OnTriggerStay(&col);
                    else
                        cc->OnTriggerExit(&col);
            }
            else if (col.a.type == ptrPxlName)
            {
                auto *pc = reg.try_get<PixelCollider>(col.a.id);
                if (pc)
                    if (IsInColBox(col))
                        pc->OnTriggerStay(&col);
                    else
                        pc->OnTriggerExit(&col);
            }
}

void SqrVsSqr(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    Collision col = {a, b};
    colBox->push_back(col);

    // Callbacks
    if (!IsInColBoxOld(col))
    {
        auto *sc = reg.try_get<SquareCollider>(a.id);
        if (sc)
            sc->OnTriggerEnter(&col);
    }
}

void SqrVsCrl(const Box &a, const Box &b, bool first)
{
    auto &reg = Game::GetRegistry();

    // Calc
    Vec2 point = {0.f, 0.f};

    auto maxX = a.pos.x + a.size.x / 2.f;
    auto minX = a.pos.x - a.size.x / 2.f;

    auto maxY = a.pos.y + a.size.y / 2.f;
    auto minY = a.pos.y - a.size.y / 2.f;

    point.x = Clamp(b.pos.x, maxX, minX);
    point.y = Clamp(b.pos.y, maxY, minY);

    auto distance = Vec2::Distance(point, b.pos);
    auto isColliding = distance < b.size.x / 2.f;

    if (!isColliding)
        return;

    // Callbacks
    Collision col = {};
    if (first)
    {
        col = {a, b};
        if (!IsInColBoxOld(col))
        {
            auto *sc = reg.try_get<SquareCollider>(a.id);
            sc->OnTriggerEnter(&col);
        }
    }
    else
    {
        col = {b, a};
        if (!IsInColBoxOld(col))
        {
            auto *cc = reg.try_get<CircleCollider>(b.id);
            cc->OnTriggerEnter(&col);
        }
    }
    colBox->push_back(col);
}

void CrlVsCrl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto dis = Vec2::Distance(a.pos, b.pos);
    auto isColliding = dis < (a.size.x / 2.f + b.size.x / 2.f);

    if (!isColliding)
        return;

    // Callbacks
    Collision col = {a, b};
    auto *cc = reg.try_get<CircleCollider>(a.id);
    if (cc)
        if (!IsInColBoxOld(col))
            cc->OnTriggerEnter(&col);
        else
            cc->OnTriggerStay(&col);
    colBox->push_back(col);
}

void SqrVsPxl(const Box &a, const Box &b, bool first)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &sr = reg.get<SpriteRenderer>(b.id);
    auto width = sr.sprite->texture->width;
    auto height = sr.sprite->texture->height;

    Vec2 pxSize = {b.size.x / width, b.size.y / height};

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

    //      Check Box Drawing
    lgfx_setcolor(1.0f, 0.1f, 0.1f, 1.0f);
    lgfx_setblend(BLEND_SOLID);

    lgfx_drawline(overTL.x, overTL.y, overBR.x, overTL.y);
    lgfx_drawline(overTL.x, overBR.y, overBR.x, overBR.y);
    lgfx_drawline(overTL.x, overTL.y, overTL.x, overBR.y);
    lgfx_drawline(overBR.x, overTL.y, overBR.x, overBR.y);

    //      Offsets
    auto offXLeft = (int)ceilf((overTL.x - bMin.x) / pxSize.x);
    auto offXRight = width - (int)ceilf((bMax.x - overBR.x) / pxSize.x);

    auto offYTop = (int)ceilf((overTL.y - bMin.y) / pxSize.y);
    auto offYBot = height - (int)ceilf((bMax.y - overBR.y) / pxSize.y);

    //      Check pixels
    auto pixels = new unsigned char[width * height * 4];
    ltex_getpixels(sr.sprite->texture, pixels);

    bool isColliding = false;

    for (int h = offYTop; h < offYBot; h++)
        for (int w = offXLeft; w < offXRight; w++)
            if (pixels[h * width * 4 + w * 4 + 3] != '\0')
            {
                isColliding = true;
                goto end;
            }

end:

    delete[] pixels;

    if (!isColliding)
        return;

    // Callbacks
    Collision col = {};
    if (first)
    {
        col = {a, b};
        if (!IsInColBoxOld(col))
        {
            auto *sc = reg.try_get<SquareCollider>(a.id);
            if (sc)
                sc->OnTriggerEnter(&col);
        }
    }
    else
    {
        col = {b, a};
        if (!IsInColBoxOld(col))
        {
            auto *pc = reg.try_get<PixelCollider>(b.id);
            if (pc)
                pc->OnTriggerEnter(&col);
        }
    }
    colBox->push_back(col);
}

void CrlVsPxl(const Box &a, const Box &b, bool first)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &sr = reg.get<SpriteRenderer>(b.id);
    auto width = sr.sprite->texture->width;
    auto height = sr.sprite->texture->height;

    Vec2 pxSize = {b.size.x / width, b.size.y / height};

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

    //      Check Box Drawing
    lgfx_setcolor(1.0f, 0.1f, 0.1f, 1.0f);
    lgfx_setblend(BLEND_SOLID);

    lgfx_drawline(overTL.x, overTL.y, overBR.x, overTL.y);
    lgfx_drawline(overTL.x, overBR.y, overBR.x, overBR.y);
    lgfx_drawline(overTL.x, overTL.y, overTL.x, overBR.y);
    lgfx_drawline(overBR.x, overTL.y, overBR.x, overBR.y);

    //      Offsets
    auto offXLeft = (int)floorf((overTL.x - bMin.x) / pxSize.x);
    auto offXRight = width - (int)floorf((bMax.x - overBR.x) / pxSize.x);

    auto offYTop = (int)floorf((overTL.y - bMin.y) / pxSize.y);
    auto offYBot = height - (int)floorf((bMax.y - overBR.y) / pxSize.y);

    //      Check pixels
    auto *pixels = new unsigned char[width * height * 4];
    ltex_getpixels(sr.sprite->texture, pixels);

    Vec2 tl = b.pos - Vec2::Hadamard(b.size, sr.pivot) + pxSize / 2.f;
    Vec2 pos = tl;

    bool isColliding = false;

    for (int h = offYTop; h < offYBot; h++)
    {
        pos.y = tl.y + pxSize.y * h;

        for (int w = offXLeft; w < offXRight; w++)
        {
            pos.x = tl.x + pxSize.x * w;

            if (!pixels[h * width * 4 + w * 4 + 3] != '\0')
                continue;

            if (Vec2::Distance(pos, a.pos) < a.size.x / 2.f)
            {
                isColliding = true;
                goto end;
            }
        }
    }

end:

    delete[] pixels;

    if (!isColliding)
        return;

    // Callbacks
    Collision col = {};
    if (first)
    {
        col = {a, b};
        if (!IsInColBoxOld(col))
        {
            auto *cc = reg.try_get<CircleCollider>(a.id);
            if (cc)
                cc->OnTriggerEnter(&col);
        }
    }
    else
    {
        col = {b, a};
        if (!IsInColBoxOld(col))
        {
            auto *pc = reg.try_get<PixelCollider>(b.id);
            if (pc)
                pc->OnTriggerEnter(&col);
        }
    }
    colBox->push_back(col);
}

void PxlVsPxl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &aSR = reg.get<SpriteRenderer>(b.id);
    auto aWidth = aSR.sprite->texture->width;
    auto aHeight = aSR.sprite->texture->height;
    auto &bSR = reg.get<SpriteRenderer>(b.id);
    auto bWidth = bSR.sprite->texture->width;
    auto bHeight = bSR.sprite->texture->height;

    Vec2 aPxSize = {a.size.x / aWidth, a.size.y / bHeight};
    Vec2 bPxSize = {b.size.x / bWidth, b.size.y / bHeight};

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

    //      Check Box Drawing
    lgfx_setcolor(1.0f, 0.1f, 0.1f, 1.0f);
    lgfx_setblend(BLEND_SOLID);

    lgfx_drawline(overTL.x, overTL.y, overBR.x, overTL.y);
    lgfx_drawline(overTL.x, overBR.y, overBR.x, overBR.y);
    lgfx_drawline(overTL.x, overTL.y, overTL.x, overBR.y);
    lgfx_drawline(overBR.x, overTL.y, overBR.x, overBR.y);

    //      Offsets
    auto aOffXLeft = (int)floorf((overTL.x - aMin.x) / aPxSize.x);
    auto aOffXRight = aWidth - (int)floorf((aMax.x - overBR.x) / aPxSize.x);
    auto aOffYTop = (int)floorf((overTL.y - aMin.y) / aPxSize.y);
    auto aOffYBot = aHeight - (int)floorf((aMax.y - overBR.y) / aPxSize.y);

    auto bOffXLeft = (int)floorf((overTL.x - bMin.x) / bPxSize.x);
    auto bOffXRight = bWidth - (int)floorf((bMax.x - overBR.x) / bPxSize.x);
    auto bOffYTop = (int)floorf((overTL.y - bMin.y) / bPxSize.y);
    auto bOffYBot = bHeight - (int)floorf((bMax.y - overBR.y) / bPxSize.y);

    //      Check pixels
    auto *aPixels = new unsigned char[aWidth * aHeight * 4];
    ltex_getpixels(aSR.sprite->texture, aPixels);

    auto *bPixels = new unsigned char[bWidth * bHeight * 4];
    ltex_getpixels(bSR.sprite->texture, bPixels);

    Vec2 aTL = a.pos - Vec2::Hadamard(a.size, aSR.pivot) + aPxSize / 2.f;
    Vec2 aPos = aTL;

    Vec2 bTL = b.pos - Vec2::Hadamard(b.size, bSR.pivot) + bPxSize / 2.f;
    Vec2 bPos = bTL;

    unsigned char alpha = '\0';
    bool isColliding = false;

    Vec2 aPxMax, aPxMin, bPxMax, bPxMin;

    for (int ah = aOffYTop; ah < aOffYBot; ah++)
    {
        aPos.y = aTL.y + aPxSize.y * ah;

        for (int aw = aOffXLeft; aw < aOffXRight; aw++)
        {
            if (aPixels[ah * aWidth * 4 + aw * 4 + 3] == '\0')
                continue;

            aPos.x = aTL.x + aPxSize.x * aw;

            aPxMax = aPos + aPxSize / 2.f;
            aPxMin = aPos - aPxSize / 2.f;

            for (int bh = bOffYTop; bh < bOffYBot; bh++)
            {
                bPos.y = bTL.y + bPxSize.y * bh;

                for (int bw = bOffXLeft; bw < bOffXRight; bw++)
                {
                    if (bPixels[bh * bWidth * 4 + bw * 4 + 3] == '\0')
                        continue;

                    bPos.x = bTL.x + bPxSize.x * bw;

                    bPxMax = bPos + bPxSize / 2.f;
                    bPxMin = bPos - bPxSize / 2.f;

                    if ((bPxMax.x > aPxMax.x && bPxMin.x > aPxMax.x) || (bPxMax.x < aPxMin.x && bPxMin.x < aPxMin.x) ||
                        (bPxMax.y > aPxMax.y && bPxMin.y > aPxMax.y) || (bPxMax.y < aPxMin.y && bPxMin.y < aPxMin.y))
                        continue;

                    isColliding = true;
                    goto end;
                }
            }
        }
    }

end:

    delete[] aPixels;
    delete[] bPixels;

    if (!isColliding)
        return;

    // Callbacks
    Collision col = {a, b};
    auto *pc = reg.try_get<PixelCollider>(a.id);
    if (pc)
        if (!IsInColBoxOld(col))
            pc->OnTriggerEnter(&col);
        else
            pc->OnTriggerStay(&col);
    colBox->push_back(col);
}
