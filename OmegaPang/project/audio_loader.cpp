#include "audio_loader.h"

#include <iostream>

static FILE *stream;

AudioLoader AudioLoader::Instance;
std::vector<Sound> AudioLoader::Sounds;

void Load(const char *file, ALCuint bufferID)
{
    errno_t err;
    const int bufferLen = 4;
    unsigned char buffer[bufferLen];

    // Open file
    err = fopen_s(&stream, file, "r");

    if (err != 0)
        throw "Error loading font file";

    // ChunkID 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    char chunkID[4] = {};
    memcpy(chunkID, buffer, 4);

    // RiffChunkSize 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    int riffChunkSize = 0;
    memcpy(&riffChunkSize, buffer, 4);

    // Format 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    char format[4] = {};
    memcpy(format, buffer, 4);

    // SubChunkId 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    char subChunkId[4] = {};
    memcpy(subChunkId, buffer, 4);

    // FmtChunkSize 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    int fmtChunkSize = 0;
    memcpy(&fmtChunkSize, buffer, 4);

    // AudioFormat 2
    memset(buffer, 0, bufferLen);
    fread(buffer + 2, 1, 2, stream);
    short int audioFormat = 0;
    memcpy(&audioFormat, buffer + 2, 2);

    // Channels 2
    memset(buffer, 0, bufferLen);
    fread(buffer + 2, 1, 2, stream);
    short int channels = 0;
    memcpy(&channels, buffer + 2, 2);

    // SampleRate 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    int sampleRate = 0;
    memcpy(&sampleRate, buffer, 4);

    // ByteRate 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    int byteRate = 0;
    memcpy(&byteRate, buffer, 4);

    // BlockAlign 2
    memset(buffer, 0, bufferLen);
    fread(buffer + 2, 1, 2, stream);
    short int blockAlign = 0;
    memcpy(&blockAlign, buffer + 2, 2);

    // BitsPerSample 2
    memset(buffer, 0, bufferLen);
    fread(buffer + 2, 1, 2, stream);
    short int bitsPerSample = 0;
    memcpy(&bitsPerSample, buffer + 2, 2);

    // ExtraParams
    if (fmtChunkSize > 16)
    {
        // ExtraParamsSize 2
        memset(buffer, 0, bufferLen);
        fread(buffer, 1, 2, stream);
        int ExtraParamsSize = (int)buffer;

        // Jump ExtraParams
        fseek(stream, ExtraParamsSize, SEEK_CUR);
    }

    // Search Data
    while (strncmp((char *)buffer, "data", 4) != 0)
        fread(buffer, 1, 4, stream);

    // DataSize 4
    memset(buffer, 0, bufferLen);
    fread(buffer, 1, 4, stream);
    int dataSize = 0;
    memcpy(&dataSize, buffer, 4);

    // DataFormat
    ALenum dataFormat = 0;
    if (bitsPerSample == 8)
        dataFormat = channels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    else if (bitsPerSample == 16)
        dataFormat = channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    // Alocate
    auto *dataBuffer = new unsigned char[dataSize];
    fread(dataBuffer, 1, dataSize, stream);
    alBufferData(bufferID, bitsPerSample, dataBuffer, dataSize, sampleRate);
}

void AudioLoader::LoadSound(const char *name, const char *file)
{
    auto newSound = Sound(name);

    alGenBuffers(1, &newSound.id);
    Load(file, newSound.id);

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
