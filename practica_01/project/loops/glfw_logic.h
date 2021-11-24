#pragma once

namespace tkl
{

class glfw_logic
{
  private:                                   // SINGLETON
    glfw_logic();                            //
    static glfw_logic instance;              //
  public:                                    //
    glfw_logic(const glfw_logic &) = delete; //
    static glfw_logic &get();                //

    void init();
    void loop();
    void exit();
};

} // namespace tkl
