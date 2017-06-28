/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _HEART_H
#define _HEART_H

#include "TexturedObject.h"

// Trivial class for displaying health
class Heart : public TexturedObject
{
public:
  Heart();
  ~Heart(void) {};

  void Update() {};
};

#endif
