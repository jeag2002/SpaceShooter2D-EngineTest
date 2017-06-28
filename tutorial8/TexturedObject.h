/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _TEXTURED_OBJECT_H
#define _TEXTURED_OBJECT_H

#include "GameObject.h"

#include "Textures.h"
#include "FixedTrig.h"

// Texture game object.  Derives from GameObject, adds texture support along with transparency and scaling.
class TexturedObject :
  public GameObject
{
public:
  // Constructor taking rectangle and texture coord definition, and a symbolic texture ID.
  TexturedObject(GLuint vBuffer, TextureID tex);
  ~TexturedObject(void) {};

  // Draws the textured object given it's current location, scale, rotation, and transparency
  void Draw();

protected:
  // Alpha value.  1 = fully opaque, 0 = fully transparent.
  GLfixed alpha;
  // Scale (size) of object.  1.0 = normal size, 2.0 = two times normal size, .5 = half size, etc.
  GLfixed scale;

  // Use these to color the object.  1, 1, 1 will make the texture look normal.  You could add a green hue to a
  // textured object by using .5, 1, .5.
  GLfixed rAlpha;
  GLfixed gAlpha;
  GLfixed bAlpha;

private:
  // Texture handle
  GLuint texture;
  // Vertex Buffer Object.  Used so that we don't have to reload vertex data each frame.
  GLuint vbo;
};


#endif
