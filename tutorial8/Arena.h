/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _ARENA_H
#define _ARENA_H

#include "texturedobject.h"

#define ARENA_WIDTH 320
#define ARENA_HEIGHT 240

/// Trivial class that handles drawing of the arena.
class Arena :
  public TexturedObject
{
public:
  Arena(void);
  ~Arena(void) {};

  void Update() {};

};

#endif
