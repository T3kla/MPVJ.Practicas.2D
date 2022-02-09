#pragma once

#include "color.h"
#include "glfw3.h"

#include <vector>

class Render
{
    friend class Game;
    static Render Instance;

  private:
    Render(){};

    char *title = nullptr;

    GLFWwindow *window = nullptr;
    int windowWidth = 1280, windowHeight = 720;

    Color bgColor = {0.f, 0.f, 0.f, 1.f};

    static void Awake();
    static void Start();
    static void Update();
    static void Fixed();
    static void Quit();

  public:
    Render(const Render &) = delete;

    static GLFWwindow *GetWindow();

    static void GetWindowSize(int &width, int &height);
    static void SetWindowSize(const int &width, const int &height);

    static const Color &GetBgColor();
    static void SetBgColor(const Color &color);

    static const char *GetTitle();
    static void SetTitle(char *text);

    static const bool GetTitleUpdate();
    static void SetTitleUpdate(bool value);

    static const void GetMainCamera(Transform *&transform, Camera *&camera);
};
