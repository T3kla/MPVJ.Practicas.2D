#include "scene_loader.h"

#include "game.h"
#include "scene.h"
#include "scene_01.h"
#include "scene_bee.h"
#include "scene_mm.h"

SceneLoader SceneLoader::Instance;

void SceneLoader::LoadScene(const char *name)
{
    // Unload
    if (Instance.current)
        Instance.current->UnloadScene();

    // Free all entities
    Game::GetRegistry().clear();

    // Search
    if (strcmp(name, "SceneMM") == 0)
        Instance.current = new SceneMM("SceneMM");
    else if (strcmp(name, "Scene01") == 0)
        Instance.current = new Scene01("Scene01");
    else if (strcmp(name, "SceneBee") == 0)
        Instance.current = new SceneBee("SceneBee");

    // Load
    if (Instance.current)
        Instance.current->LoadScene();
}
