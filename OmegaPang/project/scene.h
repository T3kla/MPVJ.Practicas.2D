#pragma once

class Scene
{
public:
	virtual ~Scene() = default;

private:
	friend class SceneLoader;

    virtual void LoadScene() = 0;
    virtual void UnloadScene() = 0;
};
