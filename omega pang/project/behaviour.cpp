#include "behaviour.h"

#include "logic.h"

Behaviour::Behaviour()
{
    Logic::Subscribe(this);
}

Behaviour::~Behaviour()
{
    Logic::UnSubscribe(this);
}
