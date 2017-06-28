/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "Arena.h"
#include "VBOAllocator.h"

  // Define a 320 X 240 square for the arena
static GLfixed buffer[] = {
  	f2x(0), f2x(0), f2x(0.0f), f2x(0.0f),
	  f2x(320),  f2x(0), f2x(1.0f), f2x(0.0f),
	  f2x(0), f2x(240), f2x(0.0f), f2x(1.0f),
	  f2x(320),  f2x(240), f2x(1.0f), f2x(1.0f)
  };

Arena::Arena(void) : TexturedObject(GetVBO(buffer), T_ARENA)
{
  x = 0;
  y = 0;
  angle = 0;
}

