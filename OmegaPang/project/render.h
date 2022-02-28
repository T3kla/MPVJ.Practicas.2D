#pragma once

#include "color.h"

struct GLFWwindow;

class Render
{
    friend class Game;
    static Render Instance;

  private:
    Render() = default;
    Render(const Render &) = delete;

    char *title = nullptr;
    GLFWwindow *window = nullptr;

    Color bgColor = {0.f, 0.f, 0.f, 1.f};

    static void Awake();
    static void Fixed();

  public:
    static GLFWwindow *GetWindow();

    static void GetWindowSize(int &width, int &height);
    static void SetWindowSize(const int &width, const int &height);

    static const Color &GetBgColor();
    static void SetBgColor(const Color &color);

    static const char *GetTitle();
    static void SetTitle(char *text);
};
