#pragma once

namespace tkl
{

class glfw_rend
{
  private:
    GLFWwindow *window;

  public:
    glfw_rend(GLFWwindow *window = nullptr);
    void init();
    void loop();
    void exit();
};

} // namespace tkl
