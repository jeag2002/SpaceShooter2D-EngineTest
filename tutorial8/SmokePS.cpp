/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "SmokePS.h"

#include "texturemanager.h"
#include "SmokeParticle.h"

// Defines how often we put out a smoke particle.  The smaller the number, the more smoke.
#define FRAMES_BETWEEN_PARTICLES 3

// Pass in an ObjectManager that will update and draw the SmokeParticles, and the duration each SmokeParticle should live
// We need an ObjectManager so that we can add any generated SmokeParticles to it during the update.
SmokePS::SmokePS(ObjectManager *pMgr) : SmokeParticleMgr(pMgr)
{
  counter = 0;
}

// Spawns a new SmokeParticle every x frames
void SmokePS::Update()
{
  counter++;

  if (!dead) {

      // Add one SmokeParticle
    if (counter % FRAMES_BETWEEN_PARTICLES == 0) {
      SmokeParticle *part = new SmokeParticle();
      // Make sure it's at the same location as the SmokeParticle system.
      part->SetXY(x, y);
      // Add this to the front, instead of the rear.  This relies on explosions being added to the rear,
      // this effectively causes the smoke trails to appear under explosions.
      SmokeParticleMgr->AddFront(part);
    }
  }
}
