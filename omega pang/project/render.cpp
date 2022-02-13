#include "render.h"

#include "entity.h"
#include "font_loader.h"
#include "game.h"
#include "gameobject.h"
#include "glfw3.h"
#include "litegfx.h"
#include "oval_renderer.h"
#include "rect_renderer.h"
#include "sprite.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stb_truetype.h"
#include "transform.h"

#include <algorithm>
#include <entt/entt.hpp>
#include <vector>

static char buffer[256];
static float w = 1280;
static float h = 720;

static std::vector<Entity *> layered;

Render Render::Instance;

void OnWindowResize(GLFWwindow *window, int w, int h)
{
    Render::SetWindowSize(w, h);
    lgfx_setup2d(w, h);
}

void Render::Awake()
{
    if (glfwInit() == 0)
        std::cout << "Panic!" << std::endl;

    // Create window
    Instance.window = glfwCreateWindow(w, h, "", nullptr, nullptr);
    glfwMakeContextCurrent(Instance.window);

    glfwSetInputMode(Instance.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowSizeCallback(Instance.window, OnWindowResize);
    lgfx_setup2d(w, h);

    // Load textures
    SpriteLoader::LoadTextures();

    // Load Fonts
    FontLoader::LoadFonts();

    // Layers buffer
    layered.reserve(10);

    // Set Background
    SetBgColor({0.5f, 0.44f, 0.37f, 1.f});
}

void Render::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Clear screen
    lgfx_clearcolorbuffer(Instance.bgColor.r, Instance.bgColor.g, Instance.bgColor.b);

    lgfx_setblend(BLEND_SOLID);

    //// Render background
    // auto &sprBg = SpriteLoader::sprBg;
    // ltex_drawrotsized(sprBg.texture, w / 2.f, h / 2.f, 0.f, 0.5f, 0.5f, w, h, sprBg.uv0.x, sprBg.uv0.y, sprBg.uv1.x,
    //                   sprBg.uv1.y);

    // Render Rects
    auto rects = reg.view<GameObject, Transform, RectRenderer>();
    for (auto [entity, go, tf, rr] : rects.each())
    {
        if (!go.isActive)
            continue;
        lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
        Vec2 fPos = tf.position + rr.offsetPosition;
        Vec2 fScl = tf.scale + rr.offsetScale;
        lgfx_drawrect(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
    }

    // Render Ovals
    auto ovals = reg.view<GameObject, Transform, OvalRenderer>();
    for (auto [entity, go, tf, rr] : ovals.each())
    {
        if (!go.isActive)
            continue;
        lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
        Vec2 fPos = tf.position + rr.offsetPosition;
        Vec2 fScl = tf.scale + rr.offsetScale;
        lgfx_drawoval(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
    }

    // Render Sprites
    lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
    const auto ByLayer = [](const SpriteRenderer &a, const SpriteRenderer &b) { return a.layer < b.layer; };
    reg.sort<SpriteRenderer>(ByLayer);
    auto sprites = reg.view<GameObject, Transform, SpriteRenderer>().use<SpriteRenderer>();

    for (auto [entity, go, tf, sr] : sprites.each())
    {
        if (!go.isActive)
            continue;

        // Animations
        auto sa = reg.try_get<SpriteAnimation>(entity);
        if (sa && sa->enable && sa->animation)
        {
            sa->count += (float)STP * 0.001f;

            if (sa->count >= sa->duration)
                sa->count = fmodf(sa->count, sa->duration);

            auto frameFreq = sa->duration / sa->animation->size();
            auto frame = (int)floorf(sa->count / frameFreq);

            sr.sprite = &sa->animation->at(frame);
        }

        // Sprite drawing
        if (sr.sprite && sr.enable)
        {
            Vec2 fPos = tf.position + sr.offsetPosition;
            Vec2 fScl = sr.size;
            float fRot = tf.rotation + sr.offsetRotation;
            lgfx_setblend(sr.blend);
            ltex_drawrotsized(sr.sprite->texture, fPos.x, fPos.y, fRot, sr.pivot.x, sr.pivot.y, fScl.x, fScl.y,
                              sr.sprite->uv0.x, sr.sprite->uv0.y, sr.sprite->uv1.x, sr.sprite->uv1.y);
        }
    }

    ltex_t *tx;
    stbtt_bakedchar *bk;
    FontLoader::GetFontOrg(tx, bk);
    auto txSize = FontLoader::GetFontTextureSize();
    stbtt_aligned_quad quad;
    float a = 0.f, b = 0.f;
    lgfx_setblend(BLEND_ALPHA);
    stbtt_GetBakedQuad(bk, txSize, txSize, 65, &a, &b, &quad, true);
    ltex_drawrotsized(tx, 300.f + a, 300.f + b, 0.f, 0.5f, 0.5f, 100.f, 100.f, quad.s0, quad.t0, quad.s1, quad.t1);
    stbtt_GetBakedQuad(bk, txSize, txSize, 66, &a, &b, &quad, true);
    ltex_drawrotsized(tx, 300.f + a, 300.f + b, 0.f, 0.5f, 0.5f, 100.f, 100.f, quad.s0, quad.t0, quad.s1, quad.t1);

    // Swap Buffers
    glfwSwapBuffers(Instance.window);
}

GLFWwindow *Render::GetWindow()
{
    return Instance.window;
}

void Render::GetWindowSize(int &width, int &height)
{
    width = w;
    height = h;
}

void Render::SetWindowSize(const int &width, const int &height)
{
    w = width;
    h = height;
}

const Color &Render::GetBgColor()
{
    return Instance.bgColor;
}

void Render::SetBgColor(const Color &color)
{
    Instance.bgColor = color;
}

const char *Render::GetTitle()
{
    return Instance.title;
}

void Render::SetTitle(char *text)
{
    Instance.title = text;
    if (Instance.title != nullptr)
        glfwSetWindowTitle(Instance.window, Instance.title);
}
