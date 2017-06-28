/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _SMOKEPS_H
#define _SMOKEPS_H

#include "ObjectManager.h"

// SmokeParticle system class. 
// Spawns a new SmokeParticle per update.  Currently SmokeParticles
// define their behaviour, and that's currently hardcoded to produce smoke.
// Should generify this in the future.
class SmokePS : public GameObject
{
public:
  // Pass in an ObjectManager that will update and draw the SmokeParticles, and the duration each SmokeParticle should live
  SmokePS(ObjectManager *pMgr);
  ~SmokePS(void) {};
  
  // Spawns a new SmokeParticle once per frame.
  void Update();
  // Nothing to draw.  Required by GameObject
  void Draw() {};

private:
  ObjectManager *SmokeParticleMgr;
  int counter;
};

#endif
