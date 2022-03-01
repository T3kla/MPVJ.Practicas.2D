#pragma once

class Scene
{
    friend class SceneLoader;

    virtual void LoadScene() = 0;
    virtual void UnloadScene() = 0;
};
