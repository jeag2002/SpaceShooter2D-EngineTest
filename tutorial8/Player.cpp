/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "Player.h"

#include <math.h>
#include "input.h"
#include "bullet.h"
#include "VBOAllocator.h"


// Define a 16 x 16 square for the player
// Orientated so that the center of the rectangle is on the players head
static  GLfixed buffer[] = {
  	f2x(-7.5), f2x(-7.5),f2x(0.0f), f2x(0.0f),
	  f2x(7.5),  f2x(-7.5),f2x(1.0f), f2x(0.0f),
	  f2x(-7.5), f2x(7.5),f2x(0.0f), f2x(1.0f),
	  f2x(7.5),  f2x(7.5), f2x(1.0f), f2x(1.0f)
  };


Player::Player(GameContext *lContext) : TexturedObject(GetVBO(buffer), T_PLAYER)
{
  context = lContext;

  type = OBJ_PLAYER;

  firePause = 0;

  hitRadius = 8;

  hitPoints = 3;
}


// Read input, move player accordingly.  If mousebutton pressed, fire a bullet.
void Player::Update() {

  // Check the mouse movement
  GLfixed da = f2x(-context->input->xChange) >> 3;

  if (da > f2x(15.0f))
    da = f2x(15.0f);

  if (da < f2x(-15.0f))
    da = f2x(-15.0f);

  // rotate the player
  angle += da;


  // Figure which way the user is trying to move
  GLfixed yDir = 0;
  GLfixed xDir = 0;

  if (context->input->up)
    xDir = f2x(1.5f);
  else if (context->input->down)
    xDir = f2x(-.750f);

  if (context->input->right)
    yDir = f2x(-1.0f);
  else if (context->input->left)
    yDir = f2x(1.0f);

  // Store our original locations
  GLfixed ox = x;
  GLfixed oy = y;

  CalcOffset(xDir, yDir, x, y);

  GameObject *hitObj = context->objMgr->CollidesWith(this);
  if (hitObj) {
    // We hit something, move us back to where we were
    x = ox;
    y = oy;
    
    Collision(hitObj);

    hitObj->Collision(this);
  }


  // Simple clipping to edge of arena
  if (x < f2x(10))
    x = f2x(10);
  if (x > f2x(310))
    x = f2x(310);
  if (y < f2x(10))
    y = f2x(10);
  if (y > f2x(230))
    y = f2x(230);



  // Check to see if it's OK to fire another bullet
  if (firePause)
    firePause--;

  // Add a bullet if appropriate
  if (context->input->fireBtn && !firePause) {
    firePause = 10;

    // Offset the bullet so it starts near the end of the gun
    GLfixed lx = x;
    GLfixed ly = y;
    CalcOffset(f2x(9), lx, ly);

    context->objMgr->Add(new Bullet(context, lx, ly, angle));
  }

}


// Gets called when something else hits this object
void Player::Collision(GameObject *obj){

  if (obj->GetType() == OBJ_ROCKET) {
    hitPoints--;
  }

  if (hitPoints <= 0)
    Die();

};
