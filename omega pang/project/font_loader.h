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

    static Font *GetFontOrgange();
    static Font *GetFontSlap();
    static void GetFontSlp(ltex_t *&texture, stbtt_bakedchar *&bake);

    static int GetFontTextureSize();
};
