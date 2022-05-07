#pragma once

#include "openal/al.h"
#include "sound.h"

#include <vector>

class AudioLoader
{
    friend class AssetLoader;

    static AudioLoader Instance;
    static std::vector<Sound> Sounds;

    static void InitBuffers();
    static void ClearBuffers();

    static void LoadSound(const char *name, const char *file);
    static void UnloadSounds();

  private:
    AudioLoader() = default;
    AudioLoader(const AudioLoader &) = delete;

  public:
    static Sound *GetSound(const char *name);
};
