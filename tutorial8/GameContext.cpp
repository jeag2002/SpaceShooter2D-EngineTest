/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "GameContext.h"

//Contains all the relevant info that a GameObject may need access to.
GameContext::GameContext(TextureManager *tMgr, ObjectManager *oMgr, ObjectManager *fMgr, Input *in)
{
  texMgr = tMgr;
  objMgr = oMgr;
  fxMgr = fMgr;
  input = in;

  score = 0;

}

GameContext::~GameContext(void)
{
}

void GameContext::AddToScore(int points) {
  score += points;
  }

int GameContext::GetScore() {
  return score;
}
