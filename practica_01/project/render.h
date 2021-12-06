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
    int windowWidth = 0;
    int windowHeight = 0;
    GLFWwindow *window = nullptr;

  public:
    static GLFWwindow *GetWindow();
    static void SetWindow(GLFWwindow *window);

    static void GetWindowSize(int &width, int &height);
    static void SetWindowSize(const int &width, const int &height);

    void Init();
    void Loop();
    void Exit();
};
