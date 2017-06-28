/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _BULLET_H
#define _BULLET_H

#include "TexturedObject.h"
#include "GameContext.h"

// Defines a bullet that the player fires.  Travels in a straight line, dies when it hits something.

class Bullet :
  public TexturedObject
{
public:
  Bullet(GameContext *lContext, GLfixed lx, GLfixed ly, GLfixed lAngle);
  ~Bullet(void) {};

  // Updates bullet's position, checks for collision
  void Update();

  GLfixed speed;

  void Collision(GameObject *obj);

private:
  GameContext *context;

};

#endif
