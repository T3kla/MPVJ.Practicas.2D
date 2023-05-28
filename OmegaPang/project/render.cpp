#include "render.h"

#include "camera.h"
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

#include <entt/entt.hpp>

constexpr float WEIGHT_NORMALIZE = 11.f;

static char titleBuffer[256];
static int w = 1280;
static int h = 720;

static Vec2 uv0 = {};
static Vec2 uv1 = {};

static std::vector<DebugSquare> DebugLines;
static std::vector<DebugSquare> DebugSquares;
static std::vector<DebugDot> DebugDots;

void UpdateOrigin();
void RenderRects();
void RenderOvals();
void RenderSprites();
void RenderUI();
void RenderDebug();

Render Render::Instance;
char *Render::Title = nullptr;
GLFWwindow *Render::Window = nullptr;
Color Render::BGColor = {0.5f, 0.44f, 0.37f, 1.f};

void OnWindowResize(GLFWwindow *window, int width, int height)
{
    Render::SetWindowSize(width, height);
    lgfx_setup2d(width, height);
}

void Render::Init()
{
    if (glfwInit() == 0)
        std::cout << "Panic!" << std::endl;

    // Create window
    Window = glfwCreateWindow(w, h, "", nullptr, nullptr);
    glfwMakeContextCurrent(Window);

    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowSizeCallback(Window, OnWindowResize);
    lgfx_setup2d(w, h);

    // Debug visualization
    DebugSquares.reserve(64);
    DebugDots.reserve(64);

    // Set Background
    SetBgColor(BGColor);

    // Set Title
    glfwSetWindowTitle(Window, titleBuffer);
}

void Render::Fixed()
{
    // Update window title

    auto fFps = static_cast<double>(Game::GetFixedFPS());
    auto uFps = static_cast<double>(Game::GetUpdateFPS());
    sprintf_s(titleBuffer, 256, "fps: %0.0f | update: %0.2f", fFps, uFps);
    glfwSetWindowTitle(Window, titleBuffer);

    // Clear screen

    lgfx_clearcolorbuffer(BGColor.r, BGColor.g, BGColor.b);
    lgfx_setblend(BLEND_SOLID);

    UpdateOrigin();
    RenderRects();
    RenderOvals();
    RenderSprites();
    RenderUI();
    RenderDebug();

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
    return BGColor;
}

void Render::SetBgColor(const Color &color)
{
    BGColor = color;
}

char *Render::GetTitle()
{
    return Title;
}

void Render::SetTitle(char *text)
{
    Title = text;

    if (Title != nullptr)
        glfwSetWindowTitle(Window, Title);
}

void Render::SetOrigin(const Vec2 &pos)
{
    lgfx_setorigin(pos.x, pos.y);
}

entt::entity Render::GetMainCamera()
{
    auto cams = Game::GetRegistry().view<GameObject, Transform, Camera>();

    for (auto [entity, go, tf, cm] : cams.each())
    {
        if (!go.isActive || !cm.main)
            continue;

        return entity;
    }

    return static_cast<entt::entity>(0);
}

void Render::SetMainCamera(entt::entity id)
{
    auto cams = Game::GetRegistry().view<GameObject, Transform, Camera>();

    for (auto [entity, go, tf, cm] : cams.each())
    {
        if (!go.isActive)
            continue;

        cm.main = entity == id;
    }
}

void UpdateOrigin()
{
    auto &reg = Game::GetRegistry();

    auto camID = Render::GetMainCamera();

    if (!reg.valid(camID))
        return;

    auto *tf = reg.try_get<Transform>(camID);

    if (tf == nullptr)
        return;

    if (reg.try_get<Camera>(camID) == nullptr)
        return;

    auto wSize = Render::GetWindowSize();
    auto pos = tf->position - wSize / 2.f;

    lgfx_setorigin(pos.x, pos.y);
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
            sa->count += static_cast<float>(STP) * 0.001f;

            if (sa->count >= sa->duration)
                sa->count = fmodf(sa->count, sa->duration);

            auto frameFreq = sa->duration / static_cast<float>(sa->animation->size());
            auto frame = static_cast<int>(floorf(sa->count / frameFreq));

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
            ltex_drawrotsized(sr.sprite->texture->texture, fPos.x, fPos.y, fRot, sr.pivot.x, sr.pivot.y, fScl.x, fScl.y,
                              uv0.x, uv0.y, uv1.x, uv1.y);
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

            auto height = (q.y1 - q.y0) / WEIGHT_NORMALIZE * tb.weight;
            auto width = (q.x1 - q.x0) / WEIGHT_NORMALIZE * tb.weight;

            // y = y + h - (q.y1 - q.y0);
            x = x + width - (q.x1 - q.x0);

            ltex_drawrotsized(tb.font->texture, x, y, 0.f, 1.f, 1.f, width, height, q.s0, q.t0, q.s1, q.t1);

            // Next letter position
            // DrawDebugDot({x, y}, 3.f, {1.f, 1.f, 1.f, 1.f}, tb.color);
            // Box around letters
            // DrawDebugSquare({x - w, y - h}, {x, y}, {1.f, 1.f, 1.f, 0.3f}, tb.color);
        }
    }
}

void RenderDebug()
{
    for (auto &&line : DebugLines)
    {
        lgfx_setcolor(line.color.r, line.color.g, line.color.b, line.color.a);
        lgfx_drawline(line.a.x, line.a.y, line.b.x, line.b.y);
        lgfx_setcolor(line.color.r, line.color.g, line.color.b, line.color.a);
        lgfx_setcolor(line.revert.r, line.revert.g, line.revert.b, line.revert.a);
    }
    DebugLines.clear();

    for (auto &&square : DebugSquares)
    {
        lgfx_setcolor(square.color.r, square.color.g, square.color.b, square.color.a);
        lgfx_drawline(square.a.x, square.a.y, square.a.x, square.b.y);
        lgfx_drawline(square.b.x, square.a.y, square.b.x, square.b.y);
        lgfx_drawline(square.a.x, square.a.y, square.b.x, square.a.y);
        lgfx_drawline(square.a.x, square.b.y, square.b.x, square.b.y);
        lgfx_setcolor(square.revert.r, square.revert.g, square.revert.b, square.revert.a);
    }
    DebugSquares.clear();

    for (auto &&dot : DebugDots)
    {
        lgfx_setcolor(dot.color.r, dot.color.g, dot.color.b, dot.color.a);
        lgfx_drawoval(dot.pos.x - dot.size / 2.f, dot.pos.y - dot.size / 2.f, dot.size, dot.size);
        lgfx_setcolor(dot.revert.r, dot.revert.g, dot.revert.b, dot.revert.a);
    }
    DebugDots.clear();
}

void Render::DrawDebugLine(const Vec2 &a, const Vec2 &b, Color color, Color revert)
{
    DebugLines.emplace_back(a, b, color, color);
}

void Render::DrawDebugSquare(const Vec2 &a, const Vec2 &b, Color color, Color revert)
{
    DebugSquares.emplace_back(a, b, color, color);
}

void Render::DrawDebugDot(const Vec2 &pos, float size, Color color, Color revert)
{
    DebugDots.emplace_back(pos, size, color, revert);
}
