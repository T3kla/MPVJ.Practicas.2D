#define LITE_GFX_IMPLEMENTATION

#include "../project/vec/vec.h"
#include <glfw3.h>
#include <iostream>
#include <litegfx.h>

using namespace std;

GLFWwindow *window = nullptr;
double mouse_pos_x, mouse_pos_y;

void game_init()
{
}

void rend_init()
{
    auto wat = glfwInit();
    if (wat == 0)
        ::cout << "Panic!" << ::endl;

    // auto monitor = glfwGetPrimaryMonitor(); // for fullscreen only
    window = glfwCreateWindow(800, 640, "lmao", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // glfwSetWindowTitle();
    // glfwSetWindowSize(GLFWwindow * window, int width, int height);
    // glfwGetWindowSize(GLFWwindow * window, int *width, int *height);
}

void game_loop()
{
    char buffer[64];
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    snprintf(buffer, 64, "%f", mouse_pos_x);
    glfwSetWindowTitle(window, buffer);
}

void rend_loop()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void game_end()
{
}

void rend_end()
{
    glfwTerminate();
}

int main()
{
    rend_init();
    game_init();

    while (glfwWindowShouldClose(window))
    {
        rend_loop();
        game_loop();
    }

    rend_end();
    game_end();

    return 0;
}
