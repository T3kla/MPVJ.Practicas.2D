#pragma once

#include "glfw3.h"

namespace tkl
{

class engine
{
  private:
    GLFWwindow *m_window = nullptr;
    double m_mouse_pos_x;
    double m_mouse_pos_y;
    double m_mouse_delta_x;
    double m_mouse_delta_y;

  public:
    void run();

    GLFWwindow *get_window();
    void set_window(GLFWwindow *window);

    void get_mouse_pos(double &pos_x, double &pos_y);
    void set_mouse_pos(const double &pos_x, const double &pos_y);
    void get_mouse_delta(double &delta_x, double &delta_y);
    void set_mouse_delta(const double &delta_x, const double &delta_y);
};

} // namespace tkl
