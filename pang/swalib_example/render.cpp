#include "render.h"

#include "game.h"
#include "gameobject.h"
#include "litegfx.h"
#include "oval_renderer.h"
#include "rect_renderer.h"
#include "scene_01.h"
#include "sprite.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_player.h"
#include "transform.h"

#include <algorithm>
#include <entt/entt.hpp>
#include <vector>

static char buffer[256];
static float w = 0;
static float h = 0;

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
    Instance.window = glfwCreateWindow(Instance.windowWidth, Instance.windowHeight, "", nullptr, nullptr);
    glfwMakeContextCurrent(Instance.window);

    glfwSetInputMode(Instance.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowSizeCallback(Instance.window, OnWindowResize);
    lgfx_setup2d(Instance.windowWidth, Instance.windowHeight);

    // Load textures
    SpriteLoader::LoadTextures();

    // Layers buffer
    layered.reserve(10);
}

void Render::Start()
{
}

void Render::Update()
{
}

void Render::Fixed()
{
    // Redraw
    lgfx_clearcolorbuffer(Instance.bgColor.r, Instance.bgColor.g, Instance.bgColor.b);

    auto &reg = Game::GetRegistry();

    // Render Rects
    auto rects = reg.view<Transform, GameObject, RectRenderer>();
    for (auto [entity, tf, go, rr] : rects.each())
    {
        if (!go.isActive)
            continue;
        lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
        Vec2 fPos = tf.position + rr.offsetPosition;
        Vec2 fScl = tf.scale + rr.offsetScale;
        lgfx_drawrect(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
    }

    // Render Ovals
    auto ovals = reg.view<Transform, GameObject, OvalRenderer>();
    for (auto [entity, tf, go, rr] : ovals.each())
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

    auto sprites = reg.view<Transform, GameObject, SpriteRenderer>().use<SpriteRenderer>();

    for (auto [entity, tf, go, sr] : sprites.each())
    {
        if (!go.isActive)
            continue;
        if (!sr.sprite)
            continue;
        Vec2 fPos = tf.position + sr.offsetPosition;
        Vec2 fScl = sr.size;
        float fRot = tf.rotation + sr.offsetRotation;
        lgfx_setblend(sr.blend);
        ltex_drawrotsized((ltex_t *)sr.sprite->texture, fPos.x, fPos.y, fRot, sr.pivot.x, sr.pivot.y, fScl.x, fScl.y,
                          sr.sprite->uv0.x, sr.sprite->uv0.y, sr.sprite->uv1.x, sr.sprite->uv1.y);
    }

    // Swap Buffers
    glfwSwapBuffers(Instance.window);
}

void Render::Quit()
{
}

const GLFWwindow *Render::GetWindow()
{
    return Instance.window;
}

void Render::GetWindowSize(int &width, int &height)
{
    width = Instance.windowWidth;
    height = Instance.windowHeight;
}

void Render::SetWindowSize(const int &width, const int &height)
{
    Instance.windowWidth = width;
    Instance.windowHeight = height;
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
