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

void on_window_resize(GLFWwindow *window, int w, int h)
{
    lgfx_setup2d(w, h);
}

void Render::Init()
{
    glfwSetWindowSizeCallback(window, on_window_resize);

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    lgfx_setup2d(w, h);
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
