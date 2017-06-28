/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _SMOKE_PARTICLE_H
#define _SMOKE_PARTICLE_H

#include "TexturedObject.h"

// Represents one SmokeParticle.  Has semi-hardcoded values for now, will abstract down the road as necessary
class SmokeParticle : public TexturedObject
{
public:
  SmokeParticle();
  ~SmokeParticle(void) {};
  
  // Required GameObject function, called once per frame.  Causes SmokeParticle to decay.
  void Update(void);

private:
  // Delta x per frame
  GLfixed dx;
  // Delta y per frame
  GLfixed dy;

  // Number of frames to live for
  int duration;

  // Alpha delta per frame
  GLfixed da;

  // Angle delta
  GLfixed dAngle;

  // scale delta
  GLfixed sa;
};

#endif
