#include "glfw_rend.h"
#include "glfw3.h"
#include "litegfx.h"

#define LITE_GFX_IMPLEMENTATION

namespace tkl
{

glfw_rend glfw_rend::instance;

glfw_rend::glfw_rend()
{
}

glfw_rend &glfw_rend::get()
{
    return instance;
}

void on_window_resize(GLFWwindow *window, int w, int h);

void glfw_rend::init()
{
    auto *window = engine::get_window();

    glfwSetWindowSizeCallback(window, on_window_resize);

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    lgfx_setup2d(w, h);
}

void glfw_rend::loop()
{
    // White out
    lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

    // Draw stuff
    lgfx_setcolor(1.f, 0.f, 0.f, 1.f);
    lgfx_drawpoint(500.f, 500.f);
    lgfx_drawline(200.f, 200.f, 500.f, 500.f);
    lgfx_drawrect(400.f, 100.f, 100.f, 200.f);
    lgfx_setcolor(0.f, 1.f, 0.f, 1.f);
    lgfx_drawrect(300.f, 100.f, 200.f, 100.f);

    // Swap buffers
    glfwSwapBuffers(engine::get_window());
}

void glfw_rend::exit()
{
}

void on_window_resize(GLFWwindow *window, int w, int h)
{
    lgfx_setup2d(w, h);
}

} // namespace tkl
