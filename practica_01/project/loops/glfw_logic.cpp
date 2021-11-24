#include "glfw_logic.h"
#include "../engine/engine.h"
#include <iostream>

namespace tkl
{

glfw_logic glfw_logic::instance;

glfw_logic::glfw_logic()
{
}

glfw_logic &glfw_logic::get()
{
    return instance;
}

void glfw_logic::init()
{
    auto wat = glfwInit();
    if (wat == 0)
        std::cout << "Panic!" << std::endl;

    auto *window = glfwCreateWindow(800, 640, "", nullptr, nullptr);
    engine::set_window(window);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // auto monitor = glfwGetPrimaryMonitor(); // for fullscreen only
    // glfwSetMouseButtonCallback(window, onMouseClicked);
    // glfwSetKeyCallback(window, onKeyPressed);
}

void glfw_logic::loop()
{
    glfwPollEvents();

    // Update mouse pos
    auto *window = engine::get_window();
    double old_mouse_pos_x, old_mouse_pos_y, mouse_pos_x, mouse_pos_y;
    engine::get_mouse_pos(old_mouse_pos_x, old_mouse_pos_y);
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    engine::set_mouse_pos(mouse_pos_x, mouse_pos_y);
    engine::set_mouse_delta(mouse_pos_x - old_mouse_pos_x, old_mouse_pos_x - mouse_pos_x);

    // Window Title
    char buffer[64];
    snprintf(buffer, 64, "%s%.0f %s%.0f", "x:", mouse_pos_x, " y:", mouse_pos_y);
    glfwSetWindowTitle(window, buffer);

    // Exit
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);
}

void glfw_logic::exit()
{
    glfwTerminate();
}

} // namespace tkl
