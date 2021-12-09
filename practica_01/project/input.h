#pragma once

class Input {
  friend class Engine;

private:                         // SINGLETON
  Input();                       //
  static Input instance;         //
public:                          //
  Input(const Input &) = delete; //
  static Input &Get();           //

private:
  char *title = nullptr;

  void Init();
  void Loop();
  void Exit();

public:
  static void SetTitle(char *text);
  static const char *GetTitle();
};
