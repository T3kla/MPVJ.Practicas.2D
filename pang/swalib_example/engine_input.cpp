#include "engine_input.h"
#include "stasis.h"
#include "sys.h"
#include "vec.h"
#include <iostream>

static double x, y;

EngineInput EngineInput::instance;
EngineInput::EngineInput() {}
EngineInput &EngineInput::Get() { return instance; };

void EngineInput::Awake() {}

void EngineInput::Start() {}

void EngineInput::Update() {}

void EngineInput::Fixed() {}

void EngineInput::Quit() {}

Vec2 EngineInput::GetMousePos() { return instance.mousePos; }
Vec2 EngineInput::GetMouseDelta() { return instance.mouseDelta; }
