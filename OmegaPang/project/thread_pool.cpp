#include "thread_pool.h"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

static int threadNum = 0;
static std::vector<std::thread> threads;
static std::mutex mutex;
static std::condition_variable condition;
static std::queue<std::function<void()>> jobs;
static bool shutdown = false;

ThreadPool ThreadPool::Instance;

void ThreadPool::Init()
{
    threadNum = std::thread::hardware_concurrency();

    threads.reserve(threadNum);

    for (int i = 0; i < threadNum; i++)
        threads.push_back(std::thread(&Loop));
}

void ThreadPool::Quit()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        shutdown = true;
    }

    condition.notify_all();

    for (auto &&t : threads)
        if (t.joinable())
            t.join();

    threads.clear();
}

int ThreadPool::GetThreadNum()
{
    return threadNum;
}

void ThreadPool::Loop()
{
    while (true)
    {
        Job job;

        {
            std::unique_lock<std::mutex> lock(mutex);

            ThreadPool *a = &Instance;
            condition.wait(lock, [a]() { return !jobs.empty() || shutdown; });

            if (shutdown)
                goto end;

            job = jobs.front();
            jobs.pop();
        }

        job();
    }
end:;
};

void ThreadPool::AddJob(Job newJob)
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        jobs.push(newJob);
    }

    condition.notify_one();
}
