#include "sys_physics.h"

#include "game.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "thread_pool.h"
#include "transform.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>

#include "render.h"

static Vec2 gravityVector = {0.f, 9.806f};

static std::vector<Box> eachCollider;  // Every Collider
static std::vector<Box> eachRigidBody; // Every Rigidbody
static std::vector<Possible> posBox;   // Every Box pair that intersects
static std::vector<Collision> colBoxA; // Collision buffer
static std::vector<Collision> colBoxB; // Collision buffer

static std::vector<Collision> *colBox = &colBoxA;    // Confirmed collisions this frame
static std::vector<Collision> *colBoxOld = &colBoxB; // Confirmed collisions last frame

static const auto *const ptrSqrName = typeid(SquareCollider).name();
static const auto *const ptrCrlName = typeid(CircleCollider).name();
static const auto *const ptrPxlName = typeid(PixelCollider).name();

static std::mutex isCollidingMutex;
static int num_threads = std::thread::hardware_concurrency();

void SqrVsSqr(const Box &, const Box &);
void SqrVsCrl(const Box &, const Box &, bool);
void CrlVsCrl(const Box &, const Box &);
void SqrVsPxl(const Box &, const Box &, bool);
void CrlVsPxl(const Box &, const Box &, bool);
void PxlVsPxl(const Box &, const Box &);

void PxlVsPxlJob(int aOffYTop, int aOffYBot, Vec2 &aTL, Vec2 &aPxSize, int aOffXLeft, int aOffXRight,
                 SpriteRenderer &aSR, int aWidth, Vec2 &aPxSizeHalf, int bOffYTop, int bOffYBot, Vec2 &bTL,
                 Vec2 &bPxSize, int bOffXLeft, int bOffXRight, int bWidth, Vec2 &bPxSizeHalf, bool *isColliding,
                 int *each);

static constexpr auto Clamp = [](float v, float max, float min) { return v >= max ? max : (v <= min ? min : v); };

static const bool IsInPosBox(const Possible &pos)
{
    return std::find(posBox.begin(), posBox.end(), pos) != posBox.end();
};

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
    eachCollider.reserve(64);
    eachRigidBody.reserve(64);
    posBox.reserve(64);
    colBoxA.reserve(64);
    colBoxB.reserve(64);
}

void SysPhysics::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Reset buffers
    eachCollider.clear();
    eachRigidBody.clear();
    posBox.clear();
    SwapColBox();

    // Apply velocity
    auto rbView = reg.view<GameObject, Transform, RigidBody>();
    auto step = (float)STP * 0.001f;
    for (auto [entity, go, tf, rb] : rbView.each())
    {
        if (!go.isActive || !rb.enable)
            continue;

        if (rb.gravity)
            rb.velocity += gravityVector * rb.gravityScale * step;

        tf.position += rb.velocity;
        rb.velocity = rb.velocity * (1.f - rb.linearDrag);
    }

    // Set views
    auto sqrView = reg.view<GameObject, Transform, SquareCollider>();
    auto crlView = reg.view<GameObject, Transform, CircleCollider>();
    auto pxlView = reg.view<GameObject, Transform, PixelCollider, SpriteRenderer>();

    auto sqrRbView = reg.view<GameObject, Transform, RigidBody, SquareCollider>();
    auto crlRbView = reg.view<GameObject, Transform, RigidBody, CircleCollider>();
    auto pxlRbView = reg.view<GameObject, Transform, RigidBody, PixelCollider, SpriteRenderer>();

    // Get colliders
    for (auto [entity, go, tf, sc] : sqrView.each())
        if (go.isActive && sc.enable)
            eachCollider.push_back({entity, tf.position + sc.center, Vec2::Hadamard(sc.size, tf.scale), ptrSqrName});

    for (auto [entity, go, tf, cc] : crlView.each())
        if (go.isActive && cc.enable)
            eachCollider.push_back(
                {entity, tf.position + cc.center, Vec2::Hadamard({cc.radius, cc.radius}, tf.scale), ptrCrlName});

    for (auto [entity, go, tf, pc, sr] : pxlView.each())
        if (go.isActive && pc.enable && sr.enable && sr.sprite)
            eachCollider.push_back({entity, tf.position, Vec2::Hadamard(sr.size, tf.scale), ptrPxlName});

    // Get rigidbodies
    for (auto [entity, go, tf, rb, sc] : sqrRbView.each())
        if (go.isActive && rb.enable && sc.enable)
            eachRigidBody.push_back({entity, tf.position + sc.center, Vec2::Hadamard(sc.size, tf.scale), ptrSqrName});

    for (auto [entity, go, tf, rb, cc] : crlRbView.each())
        if (go.isActive && rb.enable && cc.enable)
            eachRigidBody.push_back(
                {entity, tf.position + cc.center, Vec2::Hadamard({cc.radius, cc.radius}, tf.scale), ptrCrlName});

    for (auto [entity, go, tf, rb, pc, sr] : pxlRbView.each())
        if (go.isActive && rb.enable && pc.enable && sr.enable && sr.sprite)
            eachRigidBody.push_back({entity, tf.position, Vec2::Hadamard(sr.size, tf.scale), ptrPxlName});

    // Set possible collisions
    Vec2 aMax, aMin, bMax, bMin;
    for (auto &&a : eachRigidBody)
    {
        aMax = a.pos + a.size / 2.f;
        aMin = a.pos - a.size / 2.f;

        for (auto &&b : eachCollider)
        {
            if (!reg.any_of<RigidBody>(a.id))
                continue;

            if (IsInPosBox({&b, &a}))
                continue;

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

template <class T1, class T2> void Resolution(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Resolution
    Collision col1 = {a, b};
    Collision col2 = {b, a};
    colBox->push_back(col1);
    colBox->push_back(col2);

    if (!IsInColBoxOld(col1))
    {
        auto &sc = reg.get<T1>(a.id);
        sc.OnTriggerEnter(&col1);
    }
    if (!IsInColBoxOld(col2))
    {
        auto &sc = reg.get<T2>(b.id);
        sc.OnTriggerEnter(&col2);
    }
}

void SqrVsSqr(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    Resolution<SquareCollider, SquareCollider>(a, b);

    auto dir = a.pos - b.pos;

    auto disX = (a.size.x / 2.f + b.size.x / 2.f) - fabsf(dir.x);
    auto disY = (a.size.y / 2.f + b.size.y / 2.f) - fabsf(dir.y);

    Vec2 tl = Vec2(b.pos.x - b.size.x / 2.f, b.pos.y - b.size.y / 2.f);
    Vec2 br = Vec2(b.pos.x + b.size.x / 2.f, b.pos.y + b.size.y / 2.f);
    Render::DrawDebugSquare(tl, br, {1.f, 0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 1.f});

    if (disX < 0.f || disY < 0.f)
        return;

    auto &aTF = reg.get<Transform>(a.id);
    auto &aRB = reg.get<RigidBody>(a.id);

    if (disY < disX)
    {
        if (disY > 0.f)
            aRB.velocity.y = 0.f;
        aTF.position.y += dir.y > 0.f ? disY : -disY;
    }
    else
    {
        if (disX > 0.f)
            aRB.velocity.x = 0.f;
        aTF.position.x += dir.x > 0.f ? disX : -disX;
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

    if (isColliding)
        Resolution<SquareCollider, CircleCollider>(a, b);
}

void CrlVsCrl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto dis = Vec2::Distance(a.pos, b.pos);
    auto isColliding = dis < (a.size.x / 2.f + b.size.x / 2.f);

    if (isColliding)
        Resolution<CircleCollider, CircleCollider>(a, b);
}

void SqrVsPxl(const Box &a, const Box &b, bool first)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &sr = reg.get<SpriteRenderer>(b.id);
    auto width = sr.sprite->texture->texture->width;
    auto height = sr.sprite->texture->texture->height;

    Vec2 pxSize = {b.size.x / width, b.size.y / height};

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

    //      Offsets
    auto offXLeft = (int)ceilf((overTL.x - bMin.x) / pxSize.x);
    auto offXRight = width - (int)ceilf((bMax.x - overBR.x) / pxSize.x);

    auto offYTop = (int)ceilf((overTL.y - bMin.y) / pxSize.y);
    auto offYBot = height - (int)ceilf((bMax.y - overBR.y) / pxSize.y);

    //      Check pixels
    bool isColliding = false;

    for (int h = offYTop; h < offYBot; h++)
        for (int w = offXLeft; w < offXRight; w++)
            if (sr.sprite->texture->alphaMap[h * width + w] != '\0')
            {
                isColliding = true;
                goto end;
            }

end:

    if (isColliding)
        Resolution<SquareCollider, PixelCollider>(a, b);
}

void CrlVsPxl(const Box &a, const Box &b, bool first)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &sr = reg.get<SpriteRenderer>(b.id);
    auto width = sr.sprite->texture->texture->width;
    auto height = sr.sprite->texture->texture->height;

    Vec2 pxSize = {b.size.x / width, b.size.y / height};

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

    //      Offsets
    auto offXLeft = (int)floorf((overTL.x - bMin.x) / pxSize.x);
    auto offXRight = width - (int)floorf((bMax.x - overBR.x) / pxSize.x);

    auto offYTop = (int)floorf((overTL.y - bMin.y) / pxSize.y);
    auto offYBot = height - (int)floorf((bMax.y - overBR.y) / pxSize.y);

    //      Check pixels
    Vec2 tl = b.pos - Vec2::Hadamard(b.size, sr.pivot) + pxSize / 2.f;
    Vec2 pos = tl;

    bool isColliding = false;

    for (int h = offYTop; h < offYBot; h++)
    {
        pos.y = tl.y + pxSize.y * h;

        for (int w = offXLeft; w < offXRight; w++)
        {
            pos.x = tl.x + pxSize.x * w;

            if (!sr.sprite->texture->alphaMap[h * width + w] != '\0')
                continue;

            if (Vec2::Distance(pos, a.pos) < a.size.x / 2.f)
            {
                isColliding = true;
                goto end;
            }
        }
    }

end:

    if (isColliding)
        Resolution<CircleCollider, PixelCollider>(a, b);
}

void PxlVsPxl(const Box &a, const Box &b)
{
    auto &reg = Game::GetRegistry();

    // Calc
    auto &aSR = reg.get<SpriteRenderer>(b.id);
    auto aWidth = aSR.sprite->texture->texture->width;
    auto aHeight = aSR.sprite->texture->texture->height;
    auto &bSR = reg.get<SpriteRenderer>(b.id);
    auto bWidth = bSR.sprite->texture->texture->width;
    auto bHeight = bSR.sprite->texture->texture->height;

    Vec2 aPxSize = {a.size.x / aWidth, a.size.y / bHeight};
    Vec2 bPxSize = {b.size.x / bWidth, b.size.y / bHeight};
    Vec2 aPxSizeHalf = aPxSize / 2.f;
    Vec2 bPxSizeHalf = bPxSize / 2.f;

    //      Overlap
    auto aMin = a.pos - a.size / 2.f;
    auto aMax = a.pos + a.size / 2.f;
    auto bMin = b.pos - b.size / 2.f;
    auto bMax = b.pos + b.size / 2.f;

    Vec2 overTL = {Clamp(bMin.x, aMax.x, aMin.x), Clamp(bMin.y, aMax.y, aMin.y)};
    Vec2 overBR = {Clamp(bMax.x, aMax.x, aMin.x), Clamp(bMax.y, aMax.y, aMin.y)};

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
    Vec2 aTL = a.pos - Vec2::Hadamard(a.size, aSR.pivot) + aPxSizeHalf;
    Vec2 aPos = aTL;

    Vec2 bTL = b.pos - Vec2::Hadamard(b.size, bSR.pivot) + bPxSizeHalf;
    Vec2 bPos = bTL;

    unsigned char alpha = '\0';
    bool isColliding = false;

    Vec2 aPxMax, aPxMin, bPxMax, bPxMin;

    // Multithreading
    int threadNum = ThreadPool::GetThreadNum();
    int lines = aOffYBot - aOffYTop;

    if (lines < threadNum)
        threadNum = lines;

    int linesPerThread = (int)floorf((float)lines / (float)threadNum);

    int each = 0;

    for (int i = 0; i < threadNum; i++)
    {
        auto a = i * linesPerThread;
        auto b = (i + 1) * linesPerThread;

        if (i < threadNum - 1)
            ThreadPool::AddJob(std::bind(PxlVsPxlJob, aOffYTop + a, aOffYTop + b, aTL, aPxSize, aOffXLeft, aOffXRight,
                                         aSR, aWidth, aPxSizeHalf, bOffYTop, bOffYBot, bTL, bPxSize, bOffXLeft,
                                         bOffXRight, bWidth, bPxSizeHalf, &isColliding, &each));
        else
            ThreadPool::AddJob(std::bind(PxlVsPxlJob, aOffYTop + a, aOffYBot, aTL, aPxSize, aOffXLeft, aOffXRight, aSR,
                                         aWidth, aPxSizeHalf, bOffYTop, bOffYBot, bTL, bPxSize, bOffXLeft, bOffXRight,
                                         bWidth, bPxSizeHalf, &isColliding, &each));
    }

    while (each < threadNum && !isColliding)
    {
    };

    if (isColliding)
        Resolution<PixelCollider, PixelCollider>(a, b);
}

void PxlVsPxlJob(int aOffYTop, int aOffYBot, Vec2 &aTL, Vec2 &aPxSize, int aOffXLeft, int aOffXRight,
                 SpriteRenderer &aSR, int aWidth, Vec2 &aPxSizeHalf, int bOffYTop, int bOffYBot, Vec2 &bTL,
                 Vec2 &bPxSize, int bOffXLeft, int bOffXRight, int bWidth, Vec2 &bPxSizeHalf, bool *isColliding,
                 int *each)
{
    Vec2 aPos = aTL, aPxMax, aPxMin, bPos = bTL, bPxMax, bPxMin;

    for (int ah = aOffYTop; ah < aOffYBot; ah++)
    {
        aPos.y = aTL.y + aPxSize.y * ah;

        for (int aw = aOffXLeft; aw < aOffXRight; aw++)
        {
            if (aSR.sprite->texture->alphaMap[ah * aWidth + aw] == '\0')
                continue;

            aPos.x = aTL.x + aPxSize.x * aw;

            aPxMax = aPos + aPxSizeHalf;
            aPxMin = aPos - aPxSizeHalf;

            for (int bh = bOffYTop; bh < bOffYBot; bh++)
            {
                bPos.y = bTL.y + bPxSize.y * bh;

                for (int bw = bOffXLeft; bw < bOffXRight; bw++)
                {
                    if (aSR.sprite->texture->alphaMap[bh * bWidth + bw] == '\0')
                        continue;

                    if (*isColliding)
                        return;

                    bPos.x = bTL.x + bPxSize.x * bw;

                    bPxMax = bPos + bPxSizeHalf;
                    bPxMin = bPos - bPxSizeHalf;

                    if ((bPxMax.x > aPxMax.x && bPxMin.x > aPxMax.x) || (bPxMax.x < aPxMin.x && bPxMin.x < aPxMin.x) ||
                        (bPxMax.y > aPxMax.y && bPxMin.y > aPxMax.y) || (bPxMax.y < aPxMin.y && bPxMin.y < aPxMin.y))
                        continue;

                    goto found;
                }
            }
        }
    }

    isCollidingMutex.lock();
    *each += 1;
    isCollidingMutex.unlock();
    return;

found:
    isCollidingMutex.lock();
    *isColliding = true;
    isCollidingMutex.unlock();
    return;
}
