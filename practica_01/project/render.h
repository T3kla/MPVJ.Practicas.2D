#pragma once

#include "color.h"
#include "glfw3.h"

class Render {
  friend class Engine;

private:                           // SINGLETON
  Render();                        //
  static Render instance;          //
public:                            //
  Render(const Render &) = delete; //
  static Render &Get();            //

private:
  int windowWidth = 0;
  int windowHeight = 0;
  Color bgColor = {0.f, 0.f, 0.f, 0.f};
  GLFWwindow *window = nullptr;

  void Init();
  void Loop();
  void Exit();

public:
  static GLFWwindow *GetWindow();
  static void SetWindow(GLFWwindow *window);

  static void GetWindowSize(int &width, int &height);
  static void SetWindowSize(const int &width, const int &height);

  static const Color &GetBgColor();
  static void SetBgColor(const Color &color);
};
