#include "input.h"
#include "engine.h"
#include "glfw3.h"
#include "render.h"
#include "vec.h"
#include <iostream>

Input Input::instance;

Input::Input() {}

Input &Input::Get() { return instance; }

void Input::SetTitle(char *text) { instance.title = text; }

const char *Input::GetTitle() { return instance.title; }

void Input::Init() {
  auto wat = glfwInit();
  if (wat == 0)
    std::cout << "Panic!" << std::endl;

  auto *window = glfwCreateWindow(800, 640, "", nullptr, nullptr);
  Render::SetWindow(window);
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::Loop() {
  glfwPollEvents();

  // Update mouse pos
  auto *window = Render::GetWindow();
  double mouse_pos_x, mouse_pos_y;
  auto oldPos = Engine::GetMousePos();
  glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
  Engine::SetMousePos(Vec2((float)mouse_pos_x, (float)mouse_pos_y));
  Engine::SetMouseDelta(
      Vec2((float)mouse_pos_x - oldPos.x, oldPos.y - (float)mouse_pos_y));

  // Window Title
  if (title != nullptr) {
    glfwSetWindowTitle(window, title);
  }

  // Exit
  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, 1);
}

void Input::Exit() { glfwTerminate(); }
