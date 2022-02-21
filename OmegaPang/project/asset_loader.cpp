#include "asset_loader.h"

#include "font_loader.h"
#include "sprite_loader.h"

#include <filesystem>
#include <fstream>
#include <iostream>

void AssetLoader::LoadAssets()
{
    // Find files
    std::string path = "../resources/";
    std::string ext = "";

    // Load fonts
    ext = ".ttf";
    FontLoader::InitBuffers();
    for (auto &p : std::filesystem::recursive_directory_iterator(path))
        if (p.path().extension() == ext)
            FontLoader::LoadFont(p.path().stem().filename().string().c_str(), p.path().stem().string().c_str());
    FontLoader::ClearBuffers();

    // Load textures
    ext = ".png";
    for (auto &p : std::filesystem::recursive_directory_iterator(path))
        if (p.path().extension() == ext)
            SpriteLoader::LoadTexture(p.path().stem().filename().string().c_str(), p.path().stem().string().c_str());
}

void AssetLoader::UnloadAssets()
{
    FontLoader::UnloadFonts();
    SpriteLoader::UnloadTextures();
}
