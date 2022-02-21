#pragma once

#include "font.h"
#include "litegfx.h"
#include "stb_truetype.h"

#include <vector>

class AssetLoader;

class FontLoader
{
    friend AssetLoader;
    static FontLoader Instance;
    static std::vector<Font> Fonts;

    static void InitBuffers();
    static void ClearBuffers();

  private:
    FontLoader() = default;
    FontLoader(const FontLoader &) = delete;

  public:
    static void LoadFont(const char *name, const char *file);
    static Font *GetFont(const char *name);

    static void UnloadFonts();

    static int GetFontTextureSize();
};
