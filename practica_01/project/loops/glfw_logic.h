#pragma once

#include "../engine/engine.h"

namespace tkl
{

class glfw_logic
{
  private:
    engine *m_engine;

  public:
    glfw_logic(engine *eng);

    void init();
    void loop();
    void exit();
};

} // namespace tkl
