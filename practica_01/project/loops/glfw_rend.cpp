#include "glfw_rend.h"
#include "../engine/engine.h"
#include "../figures/fig_factory.h"
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
    auto *figures = figure::fig_factory::get_figures();
    for (auto &&figure : *figures)
        figure->draw();

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
