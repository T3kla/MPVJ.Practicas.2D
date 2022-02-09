#include "input.h"

#include "render.h"
#include "stasis.h"
#include "vec.h"

Input Input::Instance;

void Input::Awake()
{
}

void Input::Start()
{
}

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

void Input::Fixed()
{
}

void Input::Quit()
{
}

Vec2 Input::GetMousePos()
{
    return Instance.MousePos;
}
Vec2 Input::GetMouseDelta()
{
    return Instance.MouseDelta;
}

unsigned char Input::GetKey(KeyCode key)
{
    auto *window = Render::GetWindow();

    switch (key)
    {
    case KeyCode::W:
        return glfwGetKey(window, GLFW_KEY_W);
    case KeyCode::A:
        return glfwGetKey(window, GLFW_KEY_A);
    case KeyCode::S:
        return glfwGetKey(window, GLFW_KEY_S);
    case KeyCode::D:
        return glfwGetKey(window, GLFW_KEY_D);
    case KeyCode::Q:
        return glfwGetKey(window, GLFW_KEY_Q);
    case KeyCode::E:
        return glfwGetKey(window, GLFW_KEY_E);
    case KeyCode::Left:
        return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    case KeyCode::Right:
        return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    case KeyCode::Middle:
        return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    default:
        return 0;
    }
}
