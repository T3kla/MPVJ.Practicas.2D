#include "render.h"
#include "drawer.h"
#include "litegfx.h"

#define LITE_GFX_IMPLEMENTATION

Render Render::instance;

Render::Render()
{
}

Render &Render::Get()
{
    return instance;
}

GLFWwindow *Render::GetWindow()
{
    return Get().window;
}

void Render::SetWindow(GLFWwindow *window)
{
    Get().window = window;
}

void Render::GetWindowSize(int &width, int &height)
{
    width = Get().windowWidth;
    height = Get().windowHeight;
}

void Render::SetWindowSize(const int &width, const int &height)
{
    Get().windowWidth = width;
    Get().windowHeight = height;
}

void OnWindowResize(GLFWwindow *window, int w, int h)
{
    Render::SetWindowSize(w, h);
    lgfx_setup2d(w, h);
}

void Render::Init()
{
    glfwSetWindowSizeCallback(window, OnWindowResize);

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    lgfx_setup2d(windowWidth, windowHeight);
}

void Render::Loop()
{
    lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

    for (auto &&drawable : *Drawer::Get().GetDrawables())
        drawable->Draw();

    glfwSwapBuffers(window);
}

void Render::Exit()
{
}
