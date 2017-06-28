/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "ExplosionPS.h"
#include "ExplosionParticle.h"

// Pass in an ObjectManager that will update and draw the SmokeParticles, and the duration each SmokeParticle should live
// We need an ObjectManager so that we can add any generated SmokeParticles to it during the update.
ExplosionPS::ExplosionPS(ObjectManager *pMgr, GLfixed lx, GLfixed ly, int particles) : SmokeParticleMgr(pMgr)
{
  x = lx;
  y = ly;

  for (int i = 0; i < particles; i ++) {
    // Add one SmokeParticle
    ExplosionParticle *part = new ExplosionParticle(i%2);
    // Make sure it's at the same location as the SmokeParticle system.
    part->SetXY(x, y);
    SmokeParticleMgr->Add(part);
  }

  dead = true;
}

// Spawns a new SmokeParticle once per frame.
void ExplosionPS::Update()
{
}
