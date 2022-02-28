#pragma once

#include "font.h"

#include <vector>

class FontLoader
{
    friend class AssetLoader;

    static FontLoader Instance;
    static std::vector<Font> Fonts;

    static void InitBuffers();
    static void ClearBuffers();

    static void LoadFont(const char *name, const char *file);
    static void UnloadFonts();

  private:
    FontLoader() = default;
    FontLoader(const FontLoader &) = delete;

  public:
    static Font *GetFont(const char *name);
    static int GetFontTextureSize();
};
