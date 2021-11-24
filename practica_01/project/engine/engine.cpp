#include "engine.h"
#include "../loops/game.h"
#include "../loops/glfw_logic.h"
#include "../loops/glfw_rend.h"
#include "../time/time.h"

namespace tkl
{

engine engine::instance;

engine::engine()
{
}

engine &engine::get()
{
    return instance;
}

void engine::run()
{
    auto &logic = tkl::glfw_logic::get();
    auto &game = tkl::game::get();
    auto &rend = tkl::glfw_rend::get();
    auto &time = tkl::time::get();

    logic.init();
    game.init();
    rend.init();

    while (!glfwWindowShouldClose(get_window()))
    {
        time.update();
        logic.loop();
        game.loop();
        rend.loop();
    }

    logic.exit();
    game.exit();
    rend.exit();
}

GLFWwindow *engine::get_window()
{
    return get().m_window;
}

void engine::set_window(GLFWwindow *window)
{
    get().m_window = window;
}

void engine::get_mouse_pos(double &pos_x, double &pos_y)
{
    pos_x = get().m_mouse_pos_x;
    pos_y = get().m_mouse_pos_y;
}

void engine::set_mouse_pos(const double &pos_x, const double &pos_y)
{
    get().m_mouse_pos_x = pos_x;
    get().m_mouse_pos_y = pos_y;
}

void engine::get_mouse_delta(double &delta_x, double &delta_y)
{
    delta_x = get().m_mouse_delta_x;
    delta_y = get().m_mouse_delta_y;
}

void engine::set_mouse_delta(const double &delta_x, const double &delta_y)
{
    get().m_mouse_delta_x = delta_x;
    get().m_mouse_delta_y = delta_y;
}

} // namespace tkl
