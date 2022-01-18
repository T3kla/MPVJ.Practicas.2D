#include "engine_render.h"
#include "camera.h"
#include "engine.h"
#include "entity.h"
#include "gameobject.h"
#include "litegfx.h"
#include "oval_renderer.h"
#include "rect_renderer.h"
#include "sprite.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "transform.h"
#include "vec.h"

EngineRender EngineRender::instance;

EngineRender::EngineRender() {}

EngineRender &EngineRender::Get() { return instance; }

void OnWindowResize(GLFWwindow *window, int w, int h) {
  EngineRender::SetWindowSize(w, h);
  lgfx_setup2d(w, h);
}

void EngineRender::Awake() {
  if (glfwInit() == 0)
    std::cout << "Panic!" << std::endl;

  // Create window
  instance.window = glfwCreateWindow(
      instance.windowWidth, instance.windowHeight, "", nullptr, nullptr);
  glfwMakeContextCurrent(instance.window);

  glfwSetInputMode(instance.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetWindowSizeCallback(instance.window, OnWindowResize);
  lgfx_setup2d(instance.windowWidth, instance.windowHeight);
}

void EngineRender::Start() { SpriteLoader::LoadSprites(); }

void EngineRender::Update() {
  // Update title
  if (instance.titleUpdate)
    if (instance.title != nullptr)
      glfwSetWindowTitle(instance.window, instance.title);
}

void EngineRender::Fixed() {
  // Redraw
  lgfx_clearcolorbuffer(instance.bgColor.r, instance.bgColor.g,
                        instance.bgColor.b);

  auto &reg = Engine::GetRegistry();

  // Camera settings
  Vec2 camPos = {-instance.windowWidth / 2.f, -instance.windowHeight / 2.f};
  float camHeight = 1.f;
  auto cams = reg.view<Transform, GameObject, Camera>();
  for (auto [entity, tf, go, cm] : cams.each()) {
    if (!go.isActive)
      continue;
    if (cm.main) {
      camPos += tf.position;
      camHeight = cm.height;
    }
  }

  auto CamTreatment = [&](Vec2 &pos, Vec2 &scl) {
    pos /= camHeight;
    scl /= camHeight;
    pos -= camPos;
  };

  // Render Rects
  auto rects = reg.view<Transform, GameObject, RectRenderer>();
  for (auto [entity, tf, go, rr] : rects.each()) {
    if (!go.isActive)
      continue;
    lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
    Vec2 fPos = tf.position + rr.offsetPosition;
    Vec2 fScl = tf.scale + rr.offsetScale;
    CamTreatment(fPos, fScl);
    lgfx_drawrect(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
  }

  // Render Ovals
  auto ovals = reg.view<Transform, GameObject, OvalRenderer>();
  for (auto [entity, tf, go, rr] : ovals.each()) {
    if (!go.isActive)
      continue;
    lgfx_setcolor(rr.color.r, rr.color.g, rr.color.b, rr.color.a);
    Vec2 fPos = tf.position + rr.offsetPosition;
    Vec2 fScl = tf.scale + rr.offsetScale;
    CamTreatment(fPos, fScl);
    lgfx_drawoval(fPos.x - fScl.x / 2.f, fPos.y - fScl.y / 2.f, fScl.x, fScl.y);
  }

  // Render Sprites
  lgfx_setcolor(1.f, 1.f, 1.f, 1.f);

  const auto ByLayer = [](const SpriteRenderer &a, const SpriteRenderer &b) {
    return a.layer < b.layer;
  };

  reg.sort<SpriteRenderer>(ByLayer);

  auto sprites =
      reg.view<Transform, GameObject, SpriteRenderer>().use<SpriteRenderer>();

  for (auto [entity, tf, go, sr] : sprites.each()) {
    if (!go.isActive)
      continue;
    if (!sr.sprite)
      continue;
    Vec2 fPos = tf.position + sr.offsetPosition;
    Vec2 fScl = sr.size;
    float fRot = tf.rotation + sr.offsetRotation;
    CamTreatment(fPos, fScl);
    lgfx_setblend(sr.blend);
    ltex_drawrotsized((ltex_t *)sr.sprite->texture, fPos.x, fPos.y, fRot,
                      sr.pivot.x, sr.pivot.y, fScl.x, fScl.y, sr.sprite->uv0.x,
                      sr.sprite->uv0.y, sr.sprite->uv1.x, sr.sprite->uv1.y);
  }

  // Swap Buffers
  glfwSwapBuffers(instance.window);
}

void EngineRender::Quit() {}

GLFWwindow *EngineRender::GetWindow() { return instance.window; }

void EngineRender::SetWindow(GLFWwindow *window) { instance.window = window; }

void EngineRender::GetWindowSize(int &width, int &height) {
  width = instance.windowWidth;
  height = instance.windowHeight;
}

void EngineRender::SetWindowSize(const int &width, const int &height) {
  instance.windowWidth = width;
  instance.windowHeight = height;
}

const Color &EngineRender::GetBgColor() { return instance.bgColor; }
void EngineRender::SetBgColor(const Color &color) { instance.bgColor = color; }

const char *EngineRender::GetTitle() { return instance.title; }
void EngineRender::SetTitle(char *text) {
  instance.title = text;
  if (instance.title != nullptr)
    glfwSetWindowTitle(instance.window, instance.title);
}

const bool EngineRender::GetTitleUpdate() { return instance.titleUpdate; }
void EngineRender::SetTitleUpdate(bool value) { instance.titleUpdate = value; }

const void EngineRender::GetMainCamera(Transform *&transform, Camera *&camera) {
  auto cams = Engine::GetRegistry().view<Transform, GameObject, Camera>();

  for (auto [entity, tf, go, cm] : cams.each()) {
    if (!go.isActive)
      continue;
    if (cm.main) {
      transform = &tf;
      camera = &cm;
    }
  }
}
