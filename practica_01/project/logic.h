#pragma once

class Logic
{
  private:                         // SINGLETON
    Logic();                       //
    static Logic instance;         //
  public:                          //
    Logic(const Logic &) = delete; //
    static Logic &Get();           //

    void Init();
    void Loop();
    void Exit();
};
