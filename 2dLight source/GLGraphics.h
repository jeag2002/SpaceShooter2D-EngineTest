#ifndef GLGRAPHICS_H_INCLUDED
#define GLGRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#define GL_GLEXT_PROTOTYPES 1
#include "GLee.h"
#include <SDL_opengl.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Glut.h"
#include <gl/glext.h>
#include <string>
#include <ctime>
#include "Util.h"

#define PI 3.14159265358979323846264338379502

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

/////////////////////////////////////////////////////////////////////////
//Namespace Graphics
/////////////////////////////////////////////////////////////////////////
//Used for blitting, screen aspect changing, and image loading
//NOTE: tabbed functions are not yet ready for OpenGL
/////////////////////////////////////////////////////////////////////////

namespace GLGraphics
{
    //////Functions//////

    //Called at beginning of program run, initializes Graphics
    void Init(bool);
    void Init(int, int, bool);
    void AutoInit(); //Auto detects screen resolution and sets the app to Fullscreen mode
    void SetGLState(); //*new* Must be called after every SDL_SetVideoMode() (part of Init functions)

    //Returns an image when filename is passed (IMG_Load)
    GLuint Load(std::string); //*changed* -- taken from gpwiki -- needs to be rewritten in my style
    GLuint Load(SDL_Surface*);

    //Draws the given rect in the given color
    void DrawRect(float, float, float, float, int, int, int);
    //Draws the given line in the given color
    void DrawLine(float, float, float, float, int, int, int);
    //Draws the given point in the given color
    void DrawPoint(float, float, int, int, int);
    //Draws the given Circle in the Given color
    void DrawCircle(float, float, float, int, int, int, int);

    //Draws the given surface at the given x, y, w, and h
    void DrawImage(GLuint, float, float, float, float);
    //Draws the given surface at the given x, y, w, h, r, g, b
    void DrawImage(GLuint, float, float, float, float, float, float, float);

    //Unbinds the current texture
    void UnbindTex();

    //Start Rendering to Texture
    void RendertoTexture();
    //Stop Rendering to Texture
    void RendertoBackBuffer();

    //Flips the screen buffer
    void Flip();

    //Frees memory, called at program exit
    void Quit();


    //////Member Variables//////

    //Represents the window, images are drawn to it
    extern SDL_Surface* screen;
    extern SDL_Rect screenRect;
    extern GLuint boundTexture;

    extern GLuint textureFramebufferTexture;
    extern GLuint textureFramebuffer;

    //Used to store the width and height of the screen
    extern int winW;
    extern int winH;
}

#endif // GLGRAPHICS_H_INCLUDED
