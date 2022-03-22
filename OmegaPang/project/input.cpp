#include "input.h"

#include "game.h"
#include "glfw3.h"
#include "litegfx.h"
#include "render.h"
#include "transform.h"

Input Input::Instance;

void Input::Update()
{
    glfwPollEvents();

    // Update mouse pos
    auto *window = Render::GetWindow();
    double mouse_pos_x, mouse_pos_y;
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
    Instance.MousePos = {(float)mouse_pos_x, (float)mouse_pos_y};
    Instance.MouseDelta = Instance.MousePos - Instance.MouseOldPos;
    Instance.MouseOldPos = Instance.MousePos;

    // Exit
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, 1);
}

Vec2 Input::GetMousePos()
{
    return Instance.MousePos;
}
Vec2 Input::GetMouseDelta()
{
    return Instance.MouseDelta;
}

Vec2 Input::GetMousePosWorld()
{
    auto &reg = Game::GetRegistry();
    auto &tf = reg.get<Transform>(Render::GetMainCamera());
    auto wSize = Render::GetWindowSize();
    return tf.position + Instance.MousePos - wSize / 2.f;
}

unsigned char Input::GetKey(int key)
{
    auto *window = Render::GetWindow();

    switch (key)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        return glfwGetMouseButton(window, key);
    case GLFW_MOUSE_BUTTON_RIGHT:
        return glfwGetMouseButton(window, key);
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return glfwGetMouseButton(window, key);
    default:
        return glfwGetKey(window, key);
    }
}
