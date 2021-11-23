#define LITE_GFX_IMPLEMENTATION

#include "../project/loops/game.h"
#include "../project/loops/glfw_logic.h"
#include "../project/loops/glfw_rend.h"
#include "../project/vec/vec.h"
#include <glfw3.h>
#include <iostream>
#include <litegfx.h>

using namespace std;

GLFWwindow *window = nullptr;
double mouse_pos_x, mouse_pos_y;
double mouse_delta_x, mouse_delta_y;

void onMouseClicked(GLFWwindow *window, int button, int action, int mods);
void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

void glfw_logic_init()
{
    auto wat = glfwInit();
    if (wat == 0)
        ::cout << "Panic!" << ::endl;

    // auto monitor = glfwGetPrimaryMonitor(); // for fullscreen only
    window = glfwCreateWindow(800, 640, "lmao", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // glfwSetWindowTitle();
    // glfwSetWindowSize(GLFWwindow * window, int width, int height);
    // glfwGetWindowSize(GLFWwindow * window, int *width, int *height);

    glfwSetMouseButtonCallback(window, onMouseClicked);
    glfwSetKeyCallback(window, onKeyPressed);
}

void glfw_logic_loop()
{
    glfwPollEvents();

    // Window Title
    char buffer[64];
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    snprintf(buffer, 64, "%f", mouse_pos_x);
    glfwSetWindowTitle(window, buffer);

    // Exit
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);

    glfwSwapBuffers(window);
}

void glfw_logic_end()
{
    glfwTerminate();
}

void game_init()
{
}

void game_loop()
{
}

void game_end()
{
}

int main()
{
    glfw_logic_init();
    game_init();

    while (!glfwWindowShouldClose(window))
    {
        glfw_logic_loop();
        game_loop();
    }

    glfw_logic_end();
    game_end();

    return 0;
}

void onMouseClicked(GLFWwindow *window, int button, int action, int mods)
{
    if (GLFW_PRESS == action) // 0 = released, 1 = pressed
    {
    }
}

void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (GLFW_KEY_F == key) // 0 = released, 1 = pressed, 2 = repetition
    {
        ::cout << "Pressed F lol: " << action << ::endl;
    }
}
