#include "logic.h"
#include "engine.h"
#include "glfw3.h"
#include "render.h"
#include <iostream>

Logic Logic::instance;

Logic::Logic()
{
}

Logic &Logic::Get()
{
    return instance;
}

void Logic::Init()
{
    auto wat = glfwInit();
    if (wat == 0)
        std::cout << "Panic!" << std::endl;

    auto *window = glfwCreateWindow(800, 640, "", nullptr, nullptr);
    Render::SetWindow(window);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Logic::Loop()
{
    glfwPollEvents();

    // Update mouse pos
    auto *window = Render::GetWindow();
    double old_mouse_pos_x, old_mouse_pos_y, mouse_pos_x, mouse_pos_y;
    Engine::GetMousePos(old_mouse_pos_x, old_mouse_pos_y);
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    Engine::SetMousePos(mouse_pos_x, mouse_pos_y);
    Engine::SetMouseDelta(mouse_pos_x - old_mouse_pos_x, old_mouse_pos_x - mouse_pos_x);

    // Window Title
    char buffer[64];
    snprintf(buffer, 64, "%s%.0f %s%.0f", "x:", mouse_pos_x, " y:", mouse_pos_y);
    glfwSetWindowTitle(window, buffer);

    // Exit
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);
}

void Logic::Exit()
{
    glfwTerminate();
}
