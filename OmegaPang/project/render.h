#pragma once

#include "color.h"
#include "vec.h"

#include <entt/entt.hpp>

struct GLFWwindow;

struct DebugLine
{
    Vec2 a;
    Vec2 b;
    Color color;
    Color revert;

    DebugLine(Vec2 a, Vec2 b, const Color &color, const Color &revert)
        : a(std::move(a)), b(std::move(b)), color(color), revert(revert){};
};

struct DebugSquare
{
    Vec2 a;
    Vec2 b;
    Color color;
    Color revert;

    DebugSquare(Vec2 a, Vec2 b, const Color &color, const Color &revert)
        : a(std::move(a)), b(std::move(b)), color(color), revert(revert){};
};

struct DebugDot
{
    Vec2 pos;
    float size;
    Color color;
    Color revert;

    DebugDot(Vec2 a, float size, const Color &color, const Color &revert)
        : pos(std::move(a)), size(size), color(color), revert(revert){};
};

class Render
{
    friend class Game;
    static Render Instance;

  private:
    Render() = default;
    Render(const Render &) = delete;

    static char *Title;
    static GLFWwindow *Window;

    static Color BGColor;

    static void Init();
    static void Fixed();

  public:
    static GLFWwindow *GetWindow();

    static Vec2i GetWindowSize();
    static void SetWindowSize(const int &width, const int &height);

    static const Color &GetBgColor();
    static void SetBgColor(const Color &color);

    static char *GetTitle();
    static void SetTitle(char *text);

    static void SetOrigin(const Vec2 &pos);

    static entt::entity GetMainCamera();
    static void SetMainCamera(entt::entity id);

    // Debug

    static void DrawDebugLine(const Vec2 &a, const Vec2 &b, Color color, Color revert);
    static void DrawDebugSquare(const Vec2 &a, const Vec2 &b, Color color, Color revert);
    static void DrawDebugDot(const Vec2 &pos, float size, Color color, Color revert);
};
