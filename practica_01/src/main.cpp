#define LITE_GFX_IMPLEMENTATION

#include "../project/engine/engine.h"
#include "../project/loops/game.h"
#include "../project/loops/glfw_logic.h"
#include "../project/loops/glfw_rend.h"
#include "../project/vec/vec.h"
#include <glfw3.h>
#include <iostream>
#include <litegfx.h>

using namespace std;

int main()
{
    tkl::engine::run();
    return 0;
}
