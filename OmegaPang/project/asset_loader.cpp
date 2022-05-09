#include "asset_loader.h"

#include "audio_loader.h"
#include "font_loader.h"
#include "sprite_loader.h"

#include <filesystem>
#include <fstream>
#include <iostream>

AssetLoader AssetLoader::Instance;

void AssetLoader::LoadAssets()
{
    // Find files
    std::string path = "../resources/";
    std::string ext = "    ";

    // Load fonts
    ext = ".ttf";
    FontLoader::InitBuffers();
    for (auto &p : std::filesystem::directory_iterator(path))
        if (p.path().extension() == ext)
        {
            auto filename = p.path().filename().string();
            auto path = p.path().string();

            auto size = filename.capacity();
            char *namePtr = new char[size];
            strcpy_s(namePtr, size, filename.c_str());

            FontLoader::LoadFont(namePtr, path.c_str());
        }
    FontLoader::ClearBuffers();

    // Load textures
    ext = ".png";
    for (auto &p : std::filesystem::directory_iterator(path))
        if (p.path().extension() == ext)
        {
            auto filename = p.path().filename().string();
            auto path = p.path().string();

            auto size = filename.capacity();
            char *namePtr = new char[size];
            strcpy_s(namePtr, size, filename.c_str());

            SpriteLoader::LoadTexture(namePtr, path.c_str());
        }
    SpriteLoader::SetSprites();

    // Load Audio
    ext = ".wav";
    for (auto &p : std::filesystem::directory_iterator(path))
        if (p.path().extension() == ext)
        {
            auto filename = p.path().filename().string();
            auto path = p.path().string();

            auto size = filename.capacity();
            char *namePtr = new char[size];
            strcpy_s(namePtr, size, filename.c_str());

            AudioLoader::LoadSound(namePtr, path.c_str());
        }
}

void AssetLoader::UnloadAssets()
{
    FontLoader::UnloadFonts();
    SpriteLoader::UnloadTextures();
}
