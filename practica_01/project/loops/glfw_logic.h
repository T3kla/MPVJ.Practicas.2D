#pragma once

#include "glfw3.h"

namespace tkl
{

class glfw_logic
{
  private:
    GLFWwindow *window;

  public:
    glfw_logic(GLFWwindow *window = nullptr);
    void init();
    void loop();
    void exit();
};

} // namespace eng
