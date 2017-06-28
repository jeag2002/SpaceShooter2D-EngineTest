/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _GAME_CONTEXT_H
#define _GAME_CONTEXT_H

#include "TextureManager.h"
#include "ObjectManager.h"
#include "Input.h"

//Contains all the relevant info that a GameObject may need access to.
class GameContext
{
public:
  GameContext(TextureManager *tMgr, ObjectManager *oMgr, ObjectManager *fMgr, Input *in);
  ~GameContext(void);

  // Manages all textures used in game
  TextureManager *texMgr;
  // Manages all game objects that can collide
  ObjectManager *objMgr;
  // Manages all special FX objects
  ObjectManager *fxMgr;

  // Input class
  Input *input;

  // Adds to score
  void AddToScore(int points);
  int GetScore();

private:
  int score;

};

#endif
