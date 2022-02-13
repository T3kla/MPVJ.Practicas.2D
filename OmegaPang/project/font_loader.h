#pragma once

#include "litegfx.h"
#include "stb_truetype.h"

struct Font;

class FontLoader
{
    static FontLoader Instance;

  private:
    static Font Orange;
    static Font Slap;

  public:
    FontLoader() = default;
    FontLoader(const FontLoader &) = delete;

    static void LoadFonts();
    static void UnloadFonts();

    static Font *GetFontOrange();
    static Font *GetFontSlap();

    static int GetFontTextureSize();
};
