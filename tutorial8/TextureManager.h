/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

// Singleton class that handles texture management.
// Supports:
//   Loading of texture from 24bit BMP file
//   Conversion of raw RGB data into GL|ES textures
//   Allows access to both raw RGB and OpenGL textures.

#include <GLES/gl.h>

#include "textures.h"

// Raw texture structure.  Stores the width, height and raw RGB data  Raw data is in R, G, B format.
typedef struct {
  int w, h;
  unsigned char *pixels;
} RawTexture;

class TextureManager
{
public:
  ~TextureManager(void);

  // Get singleton instance
  static TextureManager *GetInstance(void);

  // Returns a raw RawTexture structure for the given symbolic texture.
  RawTexture *GetRawTexture(TextureID tex);
  // Returns the GL texture number for the given symbolic texture
  GLuint GetGLTexture(TextureID tex);

  // Takes two textures, premultiplies alpha, and assigns result to tex
  bool PreMultiplyAlpha(RawTexture *color, RawTexture *alpha, TextureID tex);

  // Loads all textures, converts them to raw RGB and OpenGL textures.
  bool LoadTextures();
  // Frees up any memory allocated.
  void FreeTextures();

  // Loads simple 24bit uncompressed BMP file.  
  RawTexture *LoadBMP(const char *filename);

private:
  static TextureManager *instance;
  TextureManager(void);

  RawTexture *textures[NUM_TEXTURES];
  GLuint glTextures[NUM_TEXTURES];

  bool ConvertToOGL_RGB(RawTexture *tex, GLuint oglTex);
  bool ConvertToOGL_RGBA(RawTexture *tex, GLuint oglTex);

};

#endif
