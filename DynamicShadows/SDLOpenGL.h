#ifndef SDLOPENGL
#define SDLOPENGL

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "Constructs.h"

extern unsigned int window_width, window_height, window_bpp;
extern Uint32 screen_flags;

// Holds texture data
struct TextureDesc
{
	int width, height;
	GLuint hTexture;
};

// Change viewport
void ViewOrtho(float zNear, float zFar);
void ViewPerspective(float zNear, float zFar);
void ResizeGLScene(GLsizei width, GLsizei height);

// Load an image
bool LoadIMG(const char* filename, TextureDesc &textureInfo);
SDL_Surface *ConvertToRGBA(SDL_Surface *frame);
void gluPerspective1(float fovy, double aspect, float zNear, float zFar);


// Init/shut down
bool InitSDLOpenGL();
void QuitSDLOpenGL();

// Simple 2D quad drawing function
void Draw2DQuad(const TextureDesc &textureInfo, float tiles);

#endif