#include "audio_loader.h"

#include <iostream>

static FILE *stream;

static constexpr int bufferLen = 52428800; // 50mb
static unsigned char *buffer = nullptr;

AudioLoader AudioLoader::Instance;
std::vector<Sound> AudioLoader::Sounds;

void Load(const char *file)
{
    errno_t err;

    // Open file
    err = fopen_s(&stream, file, "r");

    if (err != 0)
        throw "Error loading font file";

    fread(buffer, 4, 0, stream);

    if (strncmp((char *)buffer, "RIFF", 4) != 0)
        std::cout << "this is not a valid WAVE file" << std::endl;
}

void AudioLoader::InitBuffers()
{
    buffer = new unsigned char[bufferLen];
}

void AudioLoader::ClearBuffers()
{
    delete[] buffer;
}

void AudioLoader::LoadSound(const char *name, const char *file)
{
    auto newSound = Sound(name);

    alGenBuffers(1, &newSound.id);

    // alBufferData(newSound.id, format, data, size, freq);

    Sounds.push_back(newSound);
}

Sound *AudioLoader::GetSound(const char *name)
{
    for (auto &sound : Sounds)
        if (strcmp(sound.name, name) == 0)
            return &sound;

    return nullptr;
}

void AudioLoader::UnloadSounds()
{
    for (auto &sound : Sounds)
        alDeleteBuffers(1, &sound.id);

    Sounds.clear();
}
