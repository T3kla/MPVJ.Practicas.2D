#pragma once

#include "gameobject/gameobject.h"
#include "glfw3.h"

namespace tkl
{

class engine
{
  private:                           // SINGLETONE STUFF
    engine();                        //     Singletone constructor
    static engine instance;          //     Singletone single instance
  public:                            //
    engine(const engine &) = delete; //     Singletone copy constructor deletion
    static engine &get();            //     Singletone getter

  private:
    GLFWwindow *m_window = nullptr;
    double m_mouse_pos_x = 0.;
    double m_mouse_pos_y = 0.;
    double m_mouse_delta_x = 0.;
    double m_mouse_delta_y = 0.;

    friend gameobject;
    std::vector<gameobject *> m_gameobjects = std::vector<gameobject *>();

  public:
    static void run();

    static GLFWwindow *get_window();
    static void set_window(GLFWwindow *window);

    static void get_mouse_pos(double &pos_x, double &pos_y);
    static void set_mouse_pos(const double &pos_x, const double &pos_y);
    static void get_mouse_delta(double &delta_x, double &delta_y);
    static void set_mouse_delta(const double &delta_x, const double &delta_y);
};

} // namespace tkl
