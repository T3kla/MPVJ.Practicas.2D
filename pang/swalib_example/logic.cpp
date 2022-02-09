#include "logic.h"

#include "stasis.h"
#include <iostream>

Logic Logic::Instance;

void Logic::Subscribe(Behaviour *gameObject)
{
    // Duplication guard
    auto it = std::find(Instance.Each.begin(), Instance.Each.end(), gameObject);
    if (it != Instance.Each.end())
        return;

    Instance.Each.emplace_back(gameObject);
}

void Logic::UnSubscribe(const Behaviour *gameObject)
{
    // Not found guard
    auto it = std::find(Instance.Each.begin(), Instance.Each.end(), gameObject);
    if (it == Instance.Each.end())
        return;

    Instance.Each.erase(it);
}

const std::vector<Behaviour *> *Logic::GetGameObjects()
{
    return &Get().Each;
}

void Logic::Awake()
{
    for (auto &&go : *Instance.GetGameObjects())
        go->Awake();
}

void Logic::Start()
{
    for (auto &&go : *Instance.GetGameObjects())
        go->Start();
}

void Logic::Update()
{
    for (auto &&go : *Instance.GetGameObjects())
        go->Update();
}

void Logic::Fixed()
{
    for (auto &&go : *Instance.GetGameObjects())
        go->Fixed();
}

void Logic::Quit()
{
    for (auto &&go : *Instance.GetGameObjects())
        go->Quit();
}
