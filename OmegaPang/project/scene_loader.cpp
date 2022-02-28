#include "scene_loader.h"

#include "game.h"
#include "scene.h"
#include "scene_bee.h"
#include "scene_fonts.h"
#include "scene_pang.h"

SceneLoader SceneLoader::Instance;

void SceneLoader::LoadScene(const char *name)
{
    // Unload
    if (Instance.current)
        Instance.current->UnloadScene();

    // Free all entities
    Game::GetRegistry().clear();

    // Search
    if (strcmp(name, "SceneFonts") == 0)
        Instance.current = new SceneFonts("SceneFonts");
    else if (strcmp(name, "ScenePang") == 0)
        Instance.current = new ScenePang("ScenePang");
    else if (strcmp(name, "SceneBee") == 0)
        Instance.current = new SceneBee("SceneBee");

    // Load
    if (Instance.current)
        Instance.current->LoadScene();
}
