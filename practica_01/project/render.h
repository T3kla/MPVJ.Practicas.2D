#pragma once

#include "glfw3.h"

class Render
{
  private:                           // SINGLETON
    Render();                        //
    static Render instance;          //
  public:                            //
    Render(const Render &) = delete; //
    static Render &Get();            //

  private:
    GLFWwindow *window = nullptr;

  public:
    static GLFWwindow *GetWindow();
    static void SetWindow(GLFWwindow *window);

    void Init();
    void Loop();
    void Exit();
};
