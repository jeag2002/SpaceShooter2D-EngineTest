/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _EXPLOSION_PARTICLE_H
#define _EXPLOSION_PARTICLE_H

#include "TexturedObject.h"

// Represents one ExplosionParticle.  Has hardcoded values for now, will abstract down the road as necessary
class ExplosionParticle : public TexturedObject
{
public:
  ExplosionParticle(int color);
  ~ExplosionParticle(void) {};
  
  // Required GameObject function, called once per frame.  Causes ExplosionParticle to decay.
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

  // Deltas for red, green, and blue values.  Helps differentiate black and white-ish particles
  GLfixed dr;
  GLfixed dg;
  GLfixed db;
};

#endif
