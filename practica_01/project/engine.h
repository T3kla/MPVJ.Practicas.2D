#pragma once

#include "glfw3.h"
#include "loops/game.h"
#include "loops/glfw_logic.h"
#include "loops/glfw_rend.h"

namespace tkl
{

class engine
{
  private:
    GLFWwindow *window = nullptr;
    double mouse_pos_x, mouse_pos_y;
    double mouse_delta_x, mouse_delta_y;

  public:
    void run();
};

} // namespace tkl
