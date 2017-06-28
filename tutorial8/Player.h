/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _PLAYER_H
#define _PLAYER_H

#include "TexturedObject.h"
#include "GameContext.h"

// Represents the player

class Player :
  public TexturedObject
{
public:
  Player(GameContext *context);
  ~Player(void) {};

  // Update location and angle based off of input.
  void Update();

  // Used to update window view.
  GLfixed GetAngle() {return angle;};

  void Collision(GameObject *obj);
  int hitPoints;

private:
  GameContext *context;

  BYTE firePause;

};

#endif
