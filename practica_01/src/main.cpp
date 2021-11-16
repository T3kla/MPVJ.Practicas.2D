#define LITE_GFX_IMPLEMENTATION

#include "../project/vec/vec.h"
#include <glfw3.h>
#include <iostream>
#include <litegfx.h>

using namespace std;

void rend_init()
{
    auto wat = glfwInit();
    if (wat == 0)
        ::cout << "pos a petao" << ::endl;

    auto monitor = glfwGetPrimaryMonitor();
    auto window = glfwCreateWindow(800, 640, "lmao", monitor, GLFWwindow * share);
}

void game_init()
{
}

void rend_loop()
{
}

void game_loop()
{
}

int main()
{

    rend_init();

    return 0;
}
