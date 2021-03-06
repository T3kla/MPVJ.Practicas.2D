#include "font_loader.h"

#include "font.h"
#include "stb_truetype.h"

#include <iostream>
#include <vector>

static FILE *stream;
static std::vector<unsigned char> fontDataBuffer;

static constexpr int txSize = 512;
static constexpr int charNum = 256;

static constexpr int alphaBufferLen = txSize * txSize;
static constexpr int colorBufferLen = txSize * txSize * 4;

static unsigned char *alphaBuffer = nullptr;
static unsigned char *colorBuffer = nullptr;

FontLoader FontLoader::Instance;
std::vector<Font> FontLoader::Fonts;

void Load(const char *file, ltex_t *&texture, stbtt_bakedchar *&bakedChars)
{
    errno_t err;

    // Open file
    err = fopen_s(&stream, file, "r");

    if (err != 0)
        throw "Error loading font file";

    // Find font length
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

    // Alloc for backed chars
    bakedChars = new stbtt_bakedchar[charNum];

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

void FontLoader::InitBuffers()
{
    alphaBuffer = new unsigned char[alphaBufferLen];
    colorBuffer = new unsigned char[colorBufferLen];
}

void FontLoader::ClearBuffers()
{
    delete[] alphaBuffer;
    delete[] colorBuffer;
    fontDataBuffer.clear();
    fontDataBuffer.resize(0);
}

void FontLoader::LoadFont(const char *name, const char *file)
{
    ltex_t *tx = nullptr;
    stbtt_bakedchar *bk = nullptr;

    Load(file, tx, bk);

    Fonts.push_back({name, tx, bk});
}

Font *FontLoader::GetFont(const char *name)
{
    for (auto &font : Fonts)
        if (strcmp(font.name, name) == 0)
            return &font;

    return nullptr;
}

void FontLoader::UnloadFonts()
{
    for (auto &font : Fonts)
    {
        delete font.name;
        ltex_free(font.texture);
        delete font.bake;
    }

    Fonts.clear();
}

int FontLoader::GetFontTextureSize()
{
    return txSize;
}
