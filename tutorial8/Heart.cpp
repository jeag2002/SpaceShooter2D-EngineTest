/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "Heart.h"

#include "texturemanager.h"
#include "VBOAllocator.h"

// Define a 16 x 16 square for the smoke SmokeParticle
static  GLfixed buffer[] = {
  	f2x(-8), f2x(-8), f2x(0.0f), f2x(0.0f),
	  f2x(7),  f2x(-8),f2x(1.0f), f2x(0.0f),
	  f2x(-8), f2x(7),f2x(0.0f), f2x(1.0f),
	  f2x(7),  f2x(7), f2x(1.0f), f2x(1.0f)
  };

Heart::Heart() : TexturedObject(GetVBO(buffer), T_HEART)
{
}
