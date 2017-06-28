/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "SmokeParticle.h"
#include <stdlib.h>

#include "texturemanager.h"
#include "VBOAllocator.h"

#define PARTICLE_DURATION 30

// Define a 16 x 16 square for the smoke SmokeParticle
static  GLfixed buffer[] = {
  	f2x(-8), f2x(-8),f2x(0.0f), f2x(0.0f),
	  f2x(7),  f2x(-8),f2x(1.0f), f2x(0.0f),
	  f2x(-8), f2x(7),f2x(0.0f), f2x(1.0f),
	  f2x(7),  f2x(7),f2x(1.0f), f2x(1.0f)
  };



// Constructor that takes a duration argument, defining how many frames the SmokeParticle will live
SmokeParticle::SmokeParticle() : TexturedObject(GetVBO(buffer), T_SMOKE)
{
  // Adds some randomness to SmokeParticle life
  duration = PARTICLE_DURATION;

  // Have SmokeParticles slow drift from their starting location
  dx = f2x((rand() % 100 - 50) / 350.0f);
  dy = f2x((rand() % 100 - 50) / 350.0f);

  // Have them slowly fade away
  da = f2x(1.0f / PARTICLE_DURATION);
 
  // Rotate the SmokeParticle slowly
  dAngle = f2x((rand() % 20 - 10) / 10.0f);

  // Start the SmokeParticle at a random orientation
  angle = f2x(rand() % 360);

  // Start them out small
  scale = f2x(.5);

  // Grow the SmokeParticle slowly over time
   sa = f2x(.08f);

}

void SmokeParticle::Update(void)
{
  // Update location
  x += dx;
  y += dy;
  // Update transparency
  alpha -= da;

  rAlpha = alpha;
  gAlpha = alpha;
  bAlpha = alpha;

  // Rotate
  angle += dAngle;
  // Scale
  scale += sa;

  // Slowly die.
  duration--;
  if (duration == 0)
    dead = true;
}
