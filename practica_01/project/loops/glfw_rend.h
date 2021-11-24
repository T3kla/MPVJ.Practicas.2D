#pragma once

#include "../engine/engine.h"

namespace tkl
{

class glfw_rend
{
  private:
    engine *m_engine;

  public:
    glfw_rend(engine *eng);

    void init();
    void loop();
    void exit();
};

} // namespace tkl
