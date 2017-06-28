/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

// Singleton class that handles texture management.
//  ** NOTE **
// BMP loading is dependent on structure packing.  
// You MUST pack on at least 16 bit boundaries, anything larger will
//  cause loading issues.
// Supports:
//   Loading of texture from 24bit BMP file
//   Conversion of raw RGB data into GL|ES textures
//   Allows access to both raw RGB and OpenGL textures.

#include "texturemanager.h"

#include <fstream>
#include <iostream>

#include "defines.h"

using namespace std;

// GL_NEAREST gives a pixely old-school look, is faster.
// GL_LINEAR gives a smoother result

#define SCALE_MODE GL_NEAREST
//#define SCALE_MODE GL_LINEAR

TextureManager *TextureManager::instance = NULL;

enum TEX_LOAD {CONV_OGL_RGB, CONV_OGL_RGBA, CONV_NONE};

// List of texture filenames.  This corresponds to the enum class in TextureManager.h.  
// To add additional textures, add their filename here, and an appropriate symbolic name
// to the enum class.  Be sure to keep the symbolic and file names in the same order.
static const char *texFilenames[NUM_TEXTURES] = {"media/gfx/boss.bmp", "media/gfx/rocket.bmp", "media/gfx/rocket-a.bmp", "media/gfx/arena.bmp", "media/gfx/smoke.bmp", "media/gfx/white16.bmp", 
      "media/gfx/player.bmp", "media/gfx/bullet.bmp", "media/gfx/circle32.bmp", "media/gfx/green32.bmp",
	  "media/gfx/cloud.bmp", "media/gfx/white64.bmp",
	  "media/gfx/heart.bmp", "media/gfx/heart-alpha.bmp"
};
static const int texFormats[NUM_TEXTURES] = {CONV_OGL_RGBA, CONV_NONE, CONV_NONE, CONV_OGL_RGB, CONV_NONE, CONV_NONE, CONV_OGL_RGBA, CONV_OGL_RGBA,
  CONV_NONE, CONV_NONE, CONV_NONE, CONV_NONE, CONV_OGL_RGBA, CONV_NONE};

#pragma pack(2)

// Structure that contains the BMP file header information.
// Be sure to set your compiler to use 2 byte or 1 byte structure packing!
typedef struct { 
  U16BIT Type; 
  U32BIT Size; 
  U16BIT Reserved1; 
  U16BIT Reserved2; 
  U32BIT OffBits; 
} BMP_FILE_HEADER; 

// Structure that contains the BMP info header information.
// Be sure to set your compiler to use 2 byte or 1 byte structure packing!
typedef struct {
  U32BIT Size; 
  S32BIT Width; 
  S32BIT Height; 
  U16BIT Planes; 
  U16BIT BitCount; 
  U32BIT Compression; 
  U32BIT SizeImage; 
  S32BIT XPelsPerMeter; 
  S32BIT YPelsPerMeter; 
  U32BIT ClrUsed; 
  U32BIT ClrImportant; 
} BMP_INFO_HEADER; 

// Default constructor
TextureManager::TextureManager(void)
{
}

// Trivial destructor
TextureManager::~TextureManager(void)
{
}

// Allows access to single TextureManager instance
TextureManager *TextureManager::GetInstance(void) {

  if (instance == NULL) 
    instance = new TextureManager();
  
 return(instance);
}

// Returns the given raw RGB texture
RawTexture *TextureManager::GetRawTexture(TextureID tex) {
  if (tex < NUM_TEXTURES)
    return textures[tex];
  
  return NULL;
}

// Returns the GL texture number that corresponds to the symbolic texture name
GLuint TextureManager::GetGLTexture(TextureID tex) {
  if (tex < NUM_TEXTURES)
    return glTextures[tex];
  
  return NULL;
}


// Loads a 24 bit uncompressed BMP file.
// This does some error checking, but it's not exhaustive.
RawTexture *TextureManager::LoadBMP(const char *filename) {

  RawTexture *retVal = new RawTexture();

	BMP_FILE_HEADER fHeader;
  BMP_INFO_HEADER iHeader;

  ifstream file(filename, ios::in | ios::binary);

  if (!file) {
    cout << "Could not open " << filename << endl;
		return NULL;
  }

  file.read((char *)&fHeader, sizeof(BMP_FILE_HEADER));

  // Bitmap files are start with "BM"
  if (fHeader.Type != 0x4D42) {
    cout << filename << " is not a BMP file!" << endl;
		return NULL;
  }

  // Next read in the Info Header
  file.read((char *)&iHeader, sizeof(BMP_INFO_HEADER));

  // Make sure this is a 24 bit BMP file.
  if (iHeader.BitCount != 24) {
    cout << filename << " is not a 24 bit BMP file!" << endl;
    return NULL;
  }

  // Make sure this is an uncompressed RGB file
  if (iHeader.Compression != 0) {
    cout << filename << " is not an uncompressed RGB BMP file!" << endl;
    return NULL;
  }

  retVal->h = iHeader.Height;
  retVal->w = iHeader.Width;

  // Figure out how many bytes are in the bmp
  int numBytes = retVal->h * retVal->w * 3;

  // Seek to the beginning of the actual image bytes
  file.seekg(fHeader.OffBits);

  retVal->pixels = new unsigned char[numBytes];

  // Bail if memory allocation fails
  if (!retVal->pixels)
	{
    cout << "Failed to allocate memory for " << filename << endl;
		return NULL;
	}

  // Read in the image pixels
  file.read((char *)retVal->pixels, numBytes);

  // Reverse the order of the red and green bytes.
  unsigned char tmpRGB;
  for (int i = 0; i < retVal->w * retVal->h * 3; i += 3)
	{
		tmpRGB = retVal->pixels[i];
		retVal->pixels[i] = retVal->pixels[i+2];
		retVal->pixels[i+2] = tmpRGB;
	}

  return retVal;
}


// Converts a RawTexture into an OpenGL texture with R, G, and B components
bool TextureManager::ConvertToOGL_RGB(RawTexture *tex, GLuint oglTex) {
    // Tell OpenGL which texture we're setting up.
    glBindTexture(GL_TEXTURE_2D, oglTex);
    // Set the filter rules for both magification and shrinking.
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SCALE_MODE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SCALE_MODE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Generate a GL texture based off of the pixel data from our RGB texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w,
      tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
      tex->pixels);

    return true;
}

// Converts a RawTexture into an OpenGL texture with R, G, B, and A components
bool TextureManager::ConvertToOGL_RGBA(RawTexture *tex, GLuint oglTex) {
    // Tell OpenGL which texture we're setting up.
    glBindTexture(GL_TEXTURE_2D, oglTex);
    // Set the filter rules for both magification and shrinking.
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SCALE_MODE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SCALE_MODE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Convert the RawTexture's RGB components into an RGBA set.
    unsigned char *tempPixels = new unsigned char[tex->w * tex->h * 4];

    for (int i = 0; i < tex->w * tex->h; i++) {
      tempPixels[i * 4 + 0] = tex->pixels[i * 3 + 0];
      tempPixels[i * 4 + 1] = tex->pixels[i * 3 + 1];
      tempPixels[i * 4 + 2] = tex->pixels[i * 3 + 2];
      if (tex->pixels[i * 3 + 0] == 0 && tex->pixels[i * 3 + 1] == 0 && tex->pixels[i * 3 + 2] == 0)
        tempPixels[i * 4 + 3] = 0;
      else 
        tempPixels[i * 4 + 3] = 255;
    }

    // Generate a GL texture based off of the pixel data from our RGB texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w,
      tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
      tempPixels);

    delete [] tempPixels;

    return true;
}

// Takes two raw textures, uses the first as the color map, the second as the alpha.
// Premultiplies the color map by the alpha, and adds the alpha byte into the bitmap.
// Assigns result to oglTex texture ID
// Note that both textures must be the same width and height!
bool TextureManager::PreMultiplyAlpha(RawTexture *color, RawTexture *alpha, TextureID tex) {
  if (color->w != alpha->w || color->h != alpha->h) {
    cout << "Color and Alpha textures are not the same size! " << tex  << endl;
    return false;
  }

  // Tell OpenGL which texture we're setting up.
  glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance()->GetGLTexture(tex));
  // Set the filter rules for both magification and shrinking.
  glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, SCALE_MODE);
  glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, SCALE_MODE);
  glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Convert the RawTexture's RGB components into an RGBA set.
  unsigned char *tempPixels = new unsigned char[color->w * color->h * 4];

  for (int i = 0; i < color->w * color->h; i++) {
    // Pre muliply the alpha into the color
    tempPixels[i * 4 + 0] = (BYTE)((float)color->pixels[i * 3 + 0] * ((float)alpha->pixels[i * 3 + 0] / 255.0f));
    tempPixels[i * 4 + 1] = (BYTE)((float)color->pixels[i * 3 + 1] * ((float)alpha->pixels[i * 3 + 1] / 255.0f));
    tempPixels[i * 4 + 2] = (BYTE)((float)color->pixels[i * 3 + 2] * ((float)alpha->pixels[i * 3 + 2] / 255.0f));
    // We're assuming the alpha texture is greyscale, so we're just using the r component as alpha.
    tempPixels[i * 4 + 3] = alpha->pixels[i * 3];
  }


  // Generate a GL texture based off of the pixel data from our RGB texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, color->w,
    color->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
    tempPixels);

  delete [] tempPixels;

  return true;
}



// Loops through all known textures, loading them one at a time.
// After the raw texture is loaded, it's converted to a OpenGL texture.
// We do not release the raw texture intentionally, in case it needs to be 
// used elsewhere.
// Returns false if errors occur, true otherwise.
bool TextureManager::LoadTextures() {

  // Initialize all textures pointers to NULL to allow partial clean up if necessary
  for (int i = 0; i < NUM_TEXTURES; i++)
    textures[i] = NULL;

  glEnable(GL_TEXTURE_2D);

  // Have OpenGL generate texture numbers for all textures.
  glGenTextures(NUM_TEXTURES, glTextures);

  for (int i = 0; i < NUM_TEXTURES; i++) {
    textures[i] = LoadBMP(texFilenames[i]);
    if (textures[i] == NULL)
      return false;

    switch (texFormats[i]) {
      case CONV_OGL_RGB:
        if (!ConvertToOGL_RGB(textures[i], glTextures[i]))
          return false;
        break;
      case CONV_OGL_RGBA:
        if (!ConvertToOGL_RGBA(textures[i], glTextures[i]))
          return false;
        break;
    }
  }
  
  return true;
}

// Frees up any textures loaded.  Use with caution, as any requests for textures after this
// is called will cause serious problems.
void TextureManager::FreeTextures() {
  for (int i = 0; i < NUM_TEXTURES; i++) {
    if (textures[i])
      delete [] textures[i];
  }
}
