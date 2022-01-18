#include "font_loader.h"

#include "stb_truetype.h"
#include <fstream>

static const char *fontOrange = "resources/Orange.ttf";
static const char *fontComic = "resources/SFSlapstickComic.ttf";
static std::ifstream buffer;
static unsigned char *bufferData;

void FontLoader::LoadFonts() {
  buffer.open(fontOrange, std::ifstream::in);

  buffer.seekg(0, buffer.end);
  unsigned int fsize = buffer.tellg();
  buffer.seekg(0, buffer.beg);

  // Texture size
  auto h = 512, w = 512;

  // Font data alloc
  char *bufferData = new char[fsize];

  // Font data dump
  buffer.read(bufferData, fsize);

  // Debug
  if (buffer)
    auto lol = 0;
  else
    auto lol = 1;

  // Texture alloc
  unsigned char *pixels = new unsigned char[h * w];

  // Char data alloc
  stbtt_bakedchar *chardata = new stbtt_bakedchar[h * w];

  // Font Baking (bufferData into pixels)
  stbtt_BakeFontBitmap((unsigned char *)bufferData, 0, 10.f, pixels, h, w, 0,
                       255, chardata);

  buffer.close();
}
