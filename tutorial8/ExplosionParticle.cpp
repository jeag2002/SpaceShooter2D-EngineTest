/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "ExplosionParticle.h"
#include <stdlib.h>

#include "texturemanager.h"
#include "VBOAllocator.h"

// How many frames the particle lives.  Best to have this hardcoded for division purposes
#define PARTICLE_DURATION 50

// Define a 16 x 16 square for the smoke ExplosionParticle
static  GLfixed buffer[] = {
  	f2x(-32), f2x(-32), f2x(0.0f), f2x(0.0f),
	  f2x(32),  f2x(-32), f2x(1.0f), f2x(0.0f),
	  f2x(-32), f2x(32), f2x(0.0f), f2x(1.0f),
	  f2x(32),  f2x(32), f2x(1.0f), f2x(1.0f)
  };

// Constructor that takes a duration argument, defining how many frames the ExplosionParticle will live
ExplosionParticle::ExplosionParticle(int color) : TexturedObject(GetVBO(buffer), T_CLOUD)
{
  // Adds some randomness to ExplosionParticle life
  duration = PARTICLE_DURATION;

  // Have ExplosionParticles slow drift from their starting location
  dx = f2x((rand() % 100 - 50) / 350.0f);
  dy = f2x((rand() % 100 - 50) / 350.0f);

  // Have them slowly fade away
  // Normally we would divide by duration, but slow on non FP hardware
  da = f2x(-1.0f / PARTICLE_DURATION);

  // Start the ExplosionParticle at a random orientation
  angle = f2x(rand() % 360);

  // Start them out small
  scale = f2x(.5);

  // Grow the ExplosionParticle slowly over time
  sa = f2x(((rand() % 10) + 5) / 400.0f);

  // Rotate the ExplosionParticle slowly
  dAngle = f2x(((rand() % 16) - 8) / 10.0f);

  switch (color) {
    case 0:
      // Black-ish particle
      rAlpha = f2x(0);
      gAlpha = f2x(0);
      bAlpha = f2x(0);
      dr = 0;
      dg = 0;
      db = 0;
      break;
    case 1:
      // White-ish particle
      rAlpha = f2x(1.0);
      gAlpha = f2x(1.0);
      bAlpha = f2x(1.0);
      dr = da;
      dg = da;
      db = da;
      break;
  }
}

void ExplosionParticle::Update(void)
{
  // Update location
  x += dx;
  y += dy;
  // Update transparency
  alpha += da;
  if (alpha < 0)
    alpha = 0;

  rAlpha += dr;
  if (rAlpha > alpha)
    rAlpha = alpha;

  gAlpha += dg;
  if (gAlpha > alpha)
    gAlpha = alpha;

  bAlpha += db;
  if (bAlpha > alpha)
    bAlpha = alpha;

  // Rotate
  angle += dAngle;
  // Scale
  scale += sa;

  // Slowly die.
  duration--;
  if (duration < 0)
    dead = true;
}
