#include "behaviour.h"

#include "engine_game.h"

Behaviour::Behaviour() { EngineGame::Subscribe(this); }
Behaviour::~Behaviour() { EngineGame::UnSubscribe(this); }