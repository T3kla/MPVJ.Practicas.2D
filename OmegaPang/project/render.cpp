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
#include "textbox.h"
#include "transform.h"

#include <algorithm>
#include <entt/entt.hpp>

constexpr float WEIGHT_NORMLIZE = 11.f;

static char buffer[256];
static int w = 1280;
static int h = 720;

void RenderBG();
void RenderRects();
void RenderOvals();
void RenderSprites();
void RenderUI();

void DrawDebugLine(Vec2 a, Vec2 b, Color color, Color revert);
void DrawDebugSquare(Vec2 a, Vec2 b, Color color, Color revert);
void DrawDebugDot(Vec2 pos, float size, Color color, Color revert);

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

    // Set Background
    SetBgColor({0.5f, 0.44f, 0.37f, 1.f});
}

void Render::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Clear screen
    lgfx_clearcolorbuffer(Instance.bgColor.r, Instance.bgColor.g, Instance.bgColor.b);

    lgfx_setblend(BLEND_SOLID);

    RenderBG();
    RenderRects();
    RenderOvals();
    RenderSprites();
    RenderUI();

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

void RenderBG()
{
    auto &sprBg = SpriteLoader::sprBg;
    lgfx_setcolor(1.f, 1.f, 1.f, 1.f);
    ltex_drawrotsized(sprBg.texture, (float)w / 2.f, (float)h / 2.f, 0.f, 0.5f, 0.5f, (float)w, (float)h, sprBg.uv0.x,
                      sprBg.uv0.y, sprBg.uv1.x, sprBg.uv1.y);
}

void RenderRects()
{
    auto rects = Game::GetRegistry().view<GameObject, Transform, RectRenderer>();
    lgfx_setblend(BLEND_SOLID);

    for (auto [entity, go, tf, rr] : rects.each())
    {
        if (!go.isActive)
            continue;
        lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
        Vec2 fPos = tf.position + rr.offsetPosition;
        Vec2 fScl = tf.scale + rr.offsetScale;
        lgfx_drawrect(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
    }
}

void RenderOvals()
{
    auto ovals = Game::GetRegistry().view<GameObject, Transform, OvalRenderer>();
    lgfx_setblend(BLEND_SOLID);

    for (auto [entity, go, tf, rr] : ovals.each())
    {
        if (!go.isActive)
            continue;
        lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
        Vec2 fPos = tf.position + rr.offsetPosition;
        Vec2 fScl = tf.scale + rr.offsetScale;
        lgfx_drawoval(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
    }
}

void RenderSprites()
{
    auto &reg = Game::GetRegistry();
    lgfx_setcolor(1.f, 1.f, 1.f, 1.f);

    // Sort by layer
    const auto ByLayer = [](const SpriteRenderer &a, const SpriteRenderer &b) { return a.layer < b.layer; };
    reg.sort<SpriteRenderer>(ByLayer);
    auto sprites = reg.view<GameObject, Transform, SpriteRenderer>().use<SpriteRenderer>();

    // Draw
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
}

void RenderUI()
{
    auto &reg = Game::GetRegistry();

    // Sort by layer
    const auto ByLayer = [](const TextBox &a, const TextBox &b) { return a.layer < b.layer; };
    reg.sort<TextBox>(ByLayer);
    auto sprites = reg.view<GameObject, RectTransform, TextBox>().use<TextBox>();

    // Draw
    auto txSize = FontLoader::GetFontTextureSize();
    for (auto [entity, go, tf, tb] : sprites.each())
    {
        if (!go.isActive || !tb.enable)
            continue;

        // Debug square for Text Box
        // Vec2 a = {tf.position.x - tf.size.x / 2.f, tf.position.y - tf.size.y / 2.f};
        // Vec2 b = {tf.position.x + tf.size.x / 2.f, tf.position.y + tf.size.y / 2.f};
        // DrawDebugSquare(a, b);

        // Color and blend
        lgfx_setcolor(tb.color.r, tb.color.g, tb.color.b, tb.color.a);
        lgfx_setblend(tb.blend);

        // Quad buffer
        stbtt_aligned_quad q;

        // Initial position
        float x = tf.position.x - tf.size.x / 2.f;
        float y = tf.position.y - tf.size.y / 2.f;

        // Starting position
        // DrawDebugDot({x, y}, 10.f, {1.f, 1.f, 1.f, 1.f}, tb.color);

        for (size_t i = 0; i < tb.text.size(); i++)
        {
            stbtt_GetBakedQuad(tb.font->bake, txSize, txSize, tb.text.at(i), &x, &y, &q, true);

            auto h = (q.y1 - q.y0) / WEIGHT_NORMLIZE * tb.weight;
            auto w = (q.x1 - q.x0) / WEIGHT_NORMLIZE * tb.weight;

            // y = y + h - (q.y1 - q.y0);
            x = x + w - (q.x1 - q.x0);

            ltex_drawrotsized(tb.font->texture, x, y, 0.f, 1.f, 1.f, w, h, q.s0, q.t0, q.s1, q.t1);

            // Next letter position
            // DrawDebugDot({x, y}, 3.f, {1.f, 1.f, 1.f, 1.f}, tb.color);
            // Box around letters
            // DrawDebugSquare({x - w, y - h}, {x, y}, {1.f, 1.f, 1.f, 0.3f}, tb.color);
        }
    }
}

void DrawDebugLine(Vec2 a, Vec2 b, Color color, Color revert)
{
    lgfx_setcolor(color.r, color.g, color.b, color.a);
    lgfx_drawline(a.x, a.y, b.x, b.y);
    lgfx_setcolor(color.r, color.g, color.b, color.a);
}

void DrawDebugSquare(Vec2 a, Vec2 b, Color color, Color revert)
{
    lgfx_setcolor(color.r, color.g, color.b, color.a);
    lgfx_drawline(a.x, a.y, a.x, b.y);
    lgfx_drawline(b.x, a.y, b.x, b.y);
    lgfx_drawline(a.x, a.y, b.x, a.y);
    lgfx_drawline(a.x, b.y, b.x, b.y);
    lgfx_setcolor(revert.r, revert.g, revert.b, revert.a);
}

void DrawDebugDot(Vec2 pos, float size, Color color, Color revert)
{
    lgfx_setcolor(color.r, color.g, color.b, color.a);
    lgfx_drawoval(pos.x - size / 2.f, pos.y - size / 2.f, size, size);
    lgfx_setcolor(revert.r, revert.g, revert.b, revert.a);
}
