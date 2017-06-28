/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _EXPLOSION_PS_H
#define _EXPLOSION_PS_H

#include "ObjectManager.h"

// SmokeParticle system class. 
// Spawns a new SmokeParticle per update.  Currently SmokeParticles
// define their behaviour, and that's currently hardcoded to produce smoke.
// Should generify this in the future.
class ExplosionPS : public GameObject
{
public:
  // Pass in an ObjectManager that will update and draw the SmokeParticles, and the duration each SmokeParticle should live
  ExplosionPS(ObjectManager *pMgr, GLfixed lx, GLfixed ly, int particles);
  ~ExplosionPS(void) {};
  
  // Spawns a new SmokeParticle once per frame.
  void Update();
  // Nothing to draw.  Required by GameObject
  void Draw() {};

private:
  ObjectManager *SmokeParticleMgr;
};

#endif
