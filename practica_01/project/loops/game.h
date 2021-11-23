#pragma once

#include "glfw3.h"

namespace tkl
{

class game
{
  private:
    GLFWwindow *window;

  public:
    game(GLFWwindow *window = nullptr);
    void init();
    void loop();
    void exit();
};

} // namespace tkl
