#pragma once

namespace tkl
{

class glfw_rend
{
  private:                                 // SINGLETON
    glfw_rend();                           //
    static glfw_rend instance;             //
  public:                                  //
    glfw_rend(const glfw_rend &) = delete; //
    static glfw_rend &get();               //

    void init();
    void loop();
    void exit();
};

} // namespace tkl
