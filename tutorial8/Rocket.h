/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _ROCKET_H
#define _ROCKET_H

#include "TexturedObject.h"

#include "SmokePS.h"
#include "GameContext.h"

// Rocket class.
// Contains a SmokeParticle system that emits smoke.
class Rocket : public TexturedObject
{
public:
  // Creates a rocket at the given position, and uses the passed in ObjectManager to add smoke to
  Rocket(GameContext *lContext, GLfixed lx, GLfixed ly, GLfixed lAngle);
  ~Rocket(void);

  // Updates the rockets position, and updates it's smoke SmokeParticle system
  void Update();

  void Die();
  void Collision(GameObject *obj);


private:
  // Generates smoke
  SmokePS *smokePs;

  GLfixed speed;
  GameContext *context;
};


#endif
