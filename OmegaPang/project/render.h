#pragma once

#include "color.h"
#include <entt/entt.hpp>

struct GLFWwindow;

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

    static void Awake();
    static void Fixed();

  public:
    static GLFWwindow *GetWindow();

    static struct Vec2i GetWindowSize();
    static void SetWindowSize(const int &width, const int &height);

    static const Color &GetBgColor();
    static void SetBgColor(const Color &color);

    static char *GetTitle();
    static void SetTitle(char *text);

    static entt::entity GetMainCamera();
    static void SetMainCamera(entt::entity id);
};
