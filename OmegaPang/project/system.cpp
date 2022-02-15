#include "system.h"

#include "logic.h"

System::System()
{
    Logic::Subscribe(this);
}

System::~System()
{
    Logic::UnSubscribe(this);
}
