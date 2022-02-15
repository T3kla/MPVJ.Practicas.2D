#pragma once

class Scene;

class SceneLoader
{
    static SceneLoader Instance;

  private:
    Scene *current;

  public:
    SceneLoader() = default;
    SceneLoader(const SceneLoader &) = delete;

    static void LoadScene(const char *name);
};
