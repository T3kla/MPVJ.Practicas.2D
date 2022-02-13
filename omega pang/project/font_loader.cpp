#include "font_loader.h"

#include "font.h"
#include "stb_truetype.h"

#include <iostream>
#include <vector>

static constexpr char *fileOrg = "../resources/fontOrange.ttf";
static constexpr char *fileSlp = "../resources/fontSlap.ttf";

static FILE *stream;
static std::vector<unsigned char> fontDataBuffer;

static constexpr int txSize = 1024;
static constexpr int charNum = 256;

static constexpr int alphaBufferLen = txSize * txSize;
static constexpr int colorBufferLen = txSize * txSize * 4;

static unsigned char *alphaBuffer = nullptr;
static unsigned char *colorBuffer = nullptr;

Font FontLoader::Orange;
Font FontLoader::Slap;

void LoadFont(const char *file, ltex_t *&texture, stbtt_bakedchar *&bakedChars)
{
    errno_t err;

    // Open file
    err = fopen_s(&stream, file, "r");

    if (err != 0)
        throw "Error loading font file";

    // Find fond length
    fseek(stream, 0, SEEK_END);
    auto fontLen = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    if (fontLen < 0)
        throw "Error loading font file";

    // Resize buffer
    if (fontDataBuffer.capacity() < (size_t)fontLen)
        fontDataBuffer.resize(fontLen);

    // Dump font data to buffer
    fread(fontDataBuffer.data(), sizeof(char), fontLen, stream);

    // Close stream
    fclose(stream);

    // Alloc for alpha buffer
    bakedChars = new stbtt_bakedchar[alphaBufferLen];

    // Bake font data to alpha buffer
    err = stbtt_BakeFontBitmap(fontDataBuffer.data(), 0, 50, alphaBuffer, txSize, txSize, 0, charNum, bakedChars);

    if (err == 0)
        throw "Error baking font";

    // Color Buffer to white, then set alpha
    memset(colorBuffer, 255, colorBufferLen);
    for (size_t i = 0; i < alphaBufferLen; i++)
        colorBuffer[4 * i + 3] = alphaBuffer[i];

    // Alloc a texture
    texture = ltex_alloc(txSize, txSize, 0);
    ltex_setpixels(texture, colorBuffer);
}

void FontLoader::LoadFonts()
{
    // Generate buffers
    alphaBuffer = new unsigned char[alphaBufferLen];
    colorBuffer = new unsigned char[colorBufferLen];

    // Load fonts
    LoadFont(fileOrg, Orange.texture, Orange.bake);
    LoadFont(fileSlp, Slap.texture, Slap.bake);

    // Free Buffers
    delete[] alphaBuffer;
    delete[] colorBuffer;
    fontDataBuffer.clear();
    fontDataBuffer.resize(0);
}

void FontLoader::UnloadFonts()
{
    ltex_free(Orange.texture);
    ltex_free(Slap.texture);
    Orange.texture = nullptr;
    Slap.texture = nullptr;

    delete Orange.bake;
    delete Slap.bake;
    Orange.bake = nullptr;
    Slap.bake = nullptr;
}

Font *FontLoader::GetFontOrgange()
{
    return &Orange;
}

Font *FontLoader::GetFontSlap()
{
    return &Slap;
}

int FontLoader::GetFontTextureSize()
{
    return txSize;
}
