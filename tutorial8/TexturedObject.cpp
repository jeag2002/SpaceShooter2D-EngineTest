/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "TexturedObject.h"
#include <stdlib.h>
#include <math.h>
#include "FixedTrig.h"

#include "texturemanager.h"

// This may not currently work, as this wasn't switched over to use VBOs
//#define DRAW_HIT_CIRCLE 

#ifdef DRAW_HIT_CIRCLE
static  GLfixed circleRectCoords[] = {
  	f2x(-15.5), f2x(-15.5),
	  f2x(15.5),  f2x(-15.5),
	  f2x(-15.5), f2x(15.5),
	  f2x(15.5),  f2x(15.5)
  };

// Define texture coordinates to display an entire texture
static  GLfixed circleTexCoords[] = {
	 f2x(0.0f), f2x(0.0f),
	 f2x(1.0f), f2x(0.0f),
	 f2x(0.0f), f2x(1.0f),
	 f2x(1.0f), f2x(1.0f)
  };
#endif


// Constructor taking rectangle and texture coord definition, and a symbolic texture ID.
TexturedObject::TexturedObject(GLuint vBuffer, TextureID tex) : vbo(vBuffer), 
          texture(TextureManager::GetInstance()->GetGLTexture(tex)), alpha(f2x(1)), scale(f2x(1)),
          rAlpha(f2x(1)), gAlpha(f2x(1)), bAlpha(f2x(1))
{
}

// Draws the textured object given it's current location, scale, rotation, and transparency
void TexturedObject::Draw() {

#ifdef DRAW_HIT_CIRCLE
  if (hitRadius) 
  {
    // Point to our circle coords
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FIXED, 0, circleTexCoords);

    glColor4x(f2x(1), f2x(1), f2x(1), f2x(1));

    // Point to our rectangle corods
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FIXED, 0, circleRectCoords);

    // Select our texture
    glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance()->GetGLTexture(T_CIRCLE));
    glPushMatrix();
      glTranslatex(x, y, 0);
      // OK for floating point, this is just for debugging
      GLfixed lScale = f2x((float)hitRadius / 15.0f);
      glScalex(lScale, lScale, 0);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glPopMatrix();
  }
#endif

  // Set our transparency
  // Since we're using pre-multiplied alpha, change all color values to match.
  // There may be a better way to do this, but this seems to work
  glColor4x(rAlpha, gAlpha, bAlpha, alpha);

  // Select our texture
  glBindTexture(GL_TEXTURE_2D, texture);

  // Move, rotate, scale, and draw object.
  glPushMatrix();
    glTranslatex(x, y, 0);
    glRotatex(angle % f2x(360), 0, 0, f2x(1));
    glScalex(scale, scale, 0);

    // Point to our vertex array
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(2, GL_FIXED, 4 * sizeof(GLfixed), 0);
    glTexCoordPointer(2, GL_FIXED, 4 * sizeof(GLfixed), (GLvoid *)(2 * sizeof(GLfixed)));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glPopMatrix();

}


