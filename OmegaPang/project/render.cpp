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

static char titleBuffer[256];
static int w = 1280;
static int h = 720;

static Vec2 uv0 = {};
static Vec2 uv1 = {};

void RenderRects();
void RenderOvals();
void RenderSprites();
void RenderUI();

void DrawDebugLine(Vec2 a, Vec2 b, Color color, Color revert);
void DrawDebugSquare(Vec2 a, Vec2 b, Color color, Color revert);
void DrawDebugDot(Vec2 pos, float size, Color color, Color revert);

Render Render::Instance;
char *Render::Title = nullptr;
GLFWwindow *Render::Window = nullptr;
Color Render::BGColor = {0.5f, 0.44f, 0.37f, 1.f};

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
    Window = glfwCreateWindow(w, h, "", nullptr, nullptr);
    glfwMakeContextCurrent(Window);

    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowSizeCallback(Window, OnWindowResize);
    lgfx_setup2d(w, h);

    // Set Background
    SetBgColor(BGColor);

    // Set Title
    glfwSetWindowTitle(Window, titleBuffer);
}

void Render::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Update fpse
    auto ufps = Game::GetUpdateFPS();
    auto ffps = Game::GetFixedFPS();
    sprintf_s(titleBuffer, 256, "update: %0.0f | fps: %0.0f", ufps, ffps);
    glfwSetWindowTitle(Window, titleBuffer);

    // Clear screen
    lgfx_clearcolorbuffer(BGColor.r, BGColor.g, BGColor.b);

    lgfx_setblend(BLEND_SOLID);

    RenderRects();
    RenderOvals();
    RenderSprites();
    RenderUI();

    // Swap Buffers
    glfwSwapBuffers(Window);
}

GLFWwindow *Render::GetWindow()
{
    return Window;
}

Vec2i Render::GetWindowSize()
{
    return {w, h};
}

void Render::SetWindowSize(const int &width, const int &height)
{
    w = width;
    h = height;
}

const Color &Render::GetBgColor()
{
    return Instance.BGColor;
}

void Render::SetBgColor(const Color &color)
{
    Instance.BGColor = color;
}

char *Render::GetTitle()
{
    return Instance.Title;
}

void Render::SetTitle(char *text)
{
    Instance.Title = text;
    if (Instance.Title != nullptr)
        glfwSetWindowTitle(Window, Instance.Title);
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
            Vec2 fScl = Vec2::Hadamard(sr.size, tf.scale);
            float fRot = tf.rotation + sr.offsetRotation;

            // Reverse sprite
            if (!sr.reverse)
            {
                uv0 = {sr.sprite->uv0.x, sr.sprite->uv0.y};
                uv1 = {sr.sprite->uv1.x, sr.sprite->uv1.y};
            }
            else
            {
                uv0 = {sr.sprite->uv1.x, sr.sprite->uv0.y};
                uv1 = {sr.sprite->uv0.x, sr.sprite->uv1.y};
            }

            lgfx_setcolor(sr.color.r, sr.color.g, sr.color.b, sr.color.a);
            lgfx_setblend(sr.blend);
            ltex_drawrotsized(sr.sprite->texture, fPos.x, fPos.y, fRot, sr.pivot.x, sr.pivot.y, fScl.x, fScl.y, uv0.x,
                              uv0.y, uv1.x, uv1.y);

            // Debug Alpha visualization
            // auto width = sr.sprite->texture->width;
            // auto height = sr.sprite->texture->height;
            // Vec2 size = Vec2::Hadamard(sr.size, tf.scale);
            // Vec2 pxSize = {size.x / width, size.y / height};
            // auto pixels = new unsigned char[width * height * 4];
            // Vec2 tl = tf.position - (size * 0.5f) + pxSize / 2.f;
            // Vec2 pos = tl;
            // ltex_getpixels(sr.sprite->texture, pixels);
            // for (int h = 0; h < height; h++)
            // {
            //    pos.y = tl.y + pxSize.y * h;
            //    for (int w = 0; w < width; w++)
            //    {
            //        pos.x = tl.x + pxSize.x * w;
            //        unsigned char alpha = pixels[h * width * 4 + w * 4 + 3];

            //        if (alpha != '\0')
            //        {
            //            lgfx_drawpoint(pos.x, pos.y);
            //        }
            //    }
            // }
            // delete[] pixels;
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
