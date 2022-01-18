#include "engine_input.h"
#include "engine_render.h"
#include "entity.h"
#include "stasis.h"
#include "transform.h"
#include "vec.h"
#include <iostream>

EngineInput EngineInput::instance;

EngineInput::EngineInput() {}

EngineInput &EngineInput::Get() { return instance; };

void EngineInput::Awake() {}

void EngineInput::Start() {}

void EngineInput::Update() {
  glfwPollEvents();

  // Update mouse pos
  auto *window = EngineRender::GetWindow();
  double mouse_pos_x, mouse_pos_y;
  glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
  instance.mousePos = {(float)mouse_pos_x, (float)mouse_pos_y};
  instance.mouseDelta = instance.mousePos - instance.mouseOldPos;
  instance.mouseOldPos = instance.mousePos;

  // Exit
  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, 1);
}

void EngineInput::Fixed() {}

void EngineInput::Quit() {}

Vec2 EngineInput::GetMousePos() { return instance.mousePos; }
Vec2 EngineInput::GetMouseDelta() { return instance.mouseDelta; }
Vec2 EngineInput::GetMousePosInWorld() {
  Transform *tf = nullptr;
  Camera *cm = nullptr;
  EngineRender::GetMainCamera(tf, cm);

  if (!cm)
    return {0.f, 0.f};

  int x, y;
  EngineRender::GetWindowSize(x, y);
  return tf->position + instance.mousePos - Vec2((float)x, (float)y) / 2.f;
}

unsigned char EngineInput::GetKey(KeyCode key) {
  auto *window = EngineRender::GetWindow();

  switch (key) {
  case EngineInput::KeyCode::W:
    return glfwGetKey(window, GLFW_KEY_W);
  case EngineInput::KeyCode::A:
    return glfwGetKey(window, GLFW_KEY_A);
  case EngineInput::KeyCode::S:
    return glfwGetKey(window, GLFW_KEY_S);
  case EngineInput::KeyCode::D:
    return glfwGetKey(window, GLFW_KEY_D);
  case EngineInput::KeyCode::Q:
    return glfwGetKey(window, GLFW_KEY_Q);
  case EngineInput::KeyCode::E:
    return glfwGetKey(window, GLFW_KEY_E);
  case EngineInput::KeyCode::Left:
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  case EngineInput::KeyCode::Right:
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
  case EngineInput::KeyCode::Middle:
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
  default:
    return 0;
  }
}
