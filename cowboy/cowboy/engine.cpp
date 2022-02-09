#include "engine.h"
#include "engine_game.h"
#include "engine_input.h"
#include "engine_render.h"
#include "stasis.h"

static double fxCount = 0.;

static double dt = 0.;
static double nowFx = 0.;
static double oldFx = 0.;
static double freqFx = 0.;

auto FreqRefresh = [](double &now, double &old, double &freq) {
  now = Stasis::GetTime();
  freq = now - old;
  old = now;
};

Engine Engine::instance;

Engine::Engine() {}

Engine &Engine::Get() { return instance; };

entt::registry Engine::reg;

void Engine::Run() {
  Stasis::RefreshTime();

  EngineInput::Awake();
  EngineRender::Awake();
  EngineGame::Awake();

  EngineInput::Start();
  EngineRender::Start();
  EngineGame::Start();

  while (!glfwWindowShouldClose(EngineRender::GetWindow())) {
    Stasis::RefreshTime();

    EngineInput::Update();
    EngineGame::Update();

    dt = Stasis::GetDelta();
    fxCount += dt;
    fxCount = min(fxCount, STP * 2.);
    while (fxCount >= STP) {
      FreqRefresh(nowFx, oldFx, freqFx);
      EngineInput::Fixed();
      EngineGame::Fixed();
      EngineRender::Fixed();
      fxCount -= STP;
    }

    EngineRender::Update();
  }

  EngineInput::Quit();
  EngineGame::Quit();
  EngineRender::Quit();
}

float Engine::GetUpdateFPS() { return (float)(1000. / dt); }
float Engine::GetFixedFPS() { return (float)(1000. / freqFx); }

entt::registry &Engine::GetRegistry() { return instance.reg; }
