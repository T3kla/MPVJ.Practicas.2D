#include "logic.h"

#include "system.h"

Logic Logic::Instance;

void Logic::Subscribe(System *gameObject)
{
    // Duplication guard
    auto it = std::find(Instance.each.begin(), Instance.each.end(), gameObject);
    if (it != Instance.each.end())
        return;

    Instance.each.emplace_back(gameObject);
}

void Logic::UnSubscribe(const System *gameObject)
{
    // Not found guard
    auto it = std::find(Instance.each.begin(), Instance.each.end(), gameObject);
    if (it == Instance.each.end())
        return;

    Instance.each.erase(it);
}

const std::vector<System *> *Logic::GetSystems()
{
    return &Instance.each;
}

void Logic::Awake()
{
    for (auto &&go : *Instance.GetSystems())
        go->Awake();
}

void Logic::Start()
{
    for (auto &&go : *Instance.GetSystems())
        go->Start();
}

void Logic::Update()
{
    for (auto &&go : *Instance.GetSystems())
        go->Update();
}

void Logic::Fixed()
{
    for (auto &&go : *Instance.GetSystems())
        go->Fixed();
}

void Logic::Quit()
{
    for (auto &&go : *Instance.GetSystems())
        go->Quit();
}
