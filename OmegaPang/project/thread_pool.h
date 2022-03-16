#pragma once

#include <functional>

typedef std::function<void()> Job;

class ThreadPool
{
    friend class Game;
    static ThreadPool Instance;

  private:
    ThreadPool() = default;
    ThreadPool(const ThreadPool &) = delete;

  public:
    static void Init();
    static void Quit();

    static void Loop();
    static void AddJob(Job New_Job);

    static int GetThreadNum();
};
