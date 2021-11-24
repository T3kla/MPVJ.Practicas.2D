#include "engine.h"
#include "../loops/game.h"
#include "../loops/glfw_logic.h"
#include "../loops/glfw_rend.h"

namespace tkl
{

void engine::run()
{
    glfw_logic glfw_logic(this);
    game game(this);
    glfw_rend glfw_rend(this);

    glfw_logic.init();
    game.init();
    glfw_rend.init();

    while (!glfwWindowShouldClose(m_window))
    {
        glfw_logic.loop();
        game.loop();
        glfw_rend.loop();
    }

    glfw_logic.exit();
    game.exit();
    glfw_rend.exit();
}

GLFWwindow *engine::get_window()
{
    return m_window;
}

void engine::set_window(GLFWwindow *window)
{
    m_window = window;
}

void engine::get_mouse_pos(double &pos_x, double &pos_y)
{
    pos_x = m_mouse_pos_x;
    pos_y = m_mouse_pos_y;
}

void engine::set_mouse_pos(const double &pos_x, const double &pos_y)
{
    m_mouse_pos_x = pos_x;
    m_mouse_pos_y = pos_y;
}

void engine::get_mouse_delta(double &delta_x, double &delta_y)
{
    delta_x = m_mouse_delta_x;
    delta_y = m_mouse_delta_y;
}

void engine::set_mouse_delta(const double &delta_x, const double &delta_y)
{
    m_mouse_delta_x = delta_x;
    m_mouse_delta_y = delta_y;
}

} // namespace tkl
