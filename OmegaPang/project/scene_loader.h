#pragma once

#include "game.h"
#include "scene.h"

class SceneLoader
{
    static SceneLoader Instance;

  private:
    Scene *current = nullptr;

  public:
    SceneLoader() = default;
    SceneLoader(const SceneLoader &) = delete;

    template <class T> static void LoadScene();
};

template <class T> void SceneLoader::LoadScene()
{
    // Unload
    if (Instance.current)
        Instance.current->UnloadScene();

    // Free all entities
    Game::GetRegistry().clear();

    // Search
    Scene *newScene = new T();
    Instance.current = newScene;

    // Load
    if (Instance.current)
        Instance.current->LoadScene();
}
