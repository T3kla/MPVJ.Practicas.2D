#include "audio_loader.h"

#include "openal/AL/al.h"
#include <iostream>

static FILE *stream;

AudioLoader AudioLoader::Instance;
std::vector<Sound> AudioLoader::Sounds;

void Load(const char *file)
{
    errno_t err;

    // Open file
    err = fopen_s(&stream, file, "r");

    if (err != 0)
        throw "Error loading font file";

    fread(stream)

        in.read(buffer, 4);

    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cout << "this is not a valid WAVE file" << std::endl;
        return NULL;
    }
    in.read(buffer, 4)
}

void AudioLoader::LoadSound(const char *name, const char *file)
{
    auto newSound = Sound(name);

    alGenBuffers(1, &newSound.id);

    alBufferData(newSound.id, format, data, size, freq);

    Sounds.push_back(newSound);
}

Sound *AudioLoader::GetSound(const char *name)
{
    for (auto &font : Sounds)
        if (strcmp(font.name, name) == 0)
            return &font;

    return nullptr;
}

void AudioLoader::UnloadSounds()
{
    for (auto &sound : Sounds)
        alDeleteBuffers(1, &sound.id);

    Sounds.clear();
}
