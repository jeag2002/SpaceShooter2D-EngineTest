/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "Bullet.h"
#include "VBOAllocator.h"

#include <math.h>

// Define a 8 x 8 square for the bullet
static  GLfixed buffer[] = {
  	f2x(-4), f2x(-4), f2x(0.0f), f2x(0.0f),
	  f2x(4),  f2x(-4), f2x(1.0f), f2x(0.0f),
	  f2x(-4), f2x(4), f2x(0.0f), f2x(1.0f),
	  f2x(4),  f2x(4), f2x(1.0f), f2x(1.0f)
  };

Bullet::Bullet(GameContext *lContext, GLfixed lx, GLfixed ly, GLfixed lAngle) : TexturedObject(GetVBO(buffer), T_BULLET)
{
  // Assign starting location
  x = lx;
  y = ly;
  angle = lAngle;

  speed = f2x(4);

  type = OBJ_BULLET;

  hitRadius = 2;
  context = lContext;

}

// Updates the bullet's position
void Bullet::Update() {

  // Move it forward a bit
  CalcOffset(speed, x, y);

  // Simple clipping to arena walls
  if (x < 0 || x > f2x(320))
    dead = true;

  if (y < 0 || y > f2x(240))
    dead = true;

  GameObject *hitObj = context->objMgr->CollidesWith(this);
  if (hitObj) {
    Collision(hitObj);
    hitObj->Collision(this);
  }
}

// Something hit us
void Bullet::Collision(GameObject *obj) {
  Die();
}


