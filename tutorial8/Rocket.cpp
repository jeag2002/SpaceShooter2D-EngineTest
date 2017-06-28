/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "Rocket.h"

#include "ExplosionPS.h"
#include "VBOAllocator.h"

// Define a 16 x 16 square for the rocket
static  GLfixed buffer[] = {
  	f2x(-7.5), f2x(-7.5),f2x(0.0f), f2x(0.0f),
	  f2x(7.5),  f2x(-7.5),f2x(1.0f), f2x(0.0f),
	  f2x(-7.5), f2x(7.5),f2x(0.0f), f2x(1.0f),
	  f2x(7.5),  f2x(7.5), f2x(1.0f), f2x(1.0f)
  };


// Creates a rocket at the given position, and uses the passed in ObjectManager to render the smoke
Rocket::Rocket(GameContext *lContext, GLfixed lx, GLfixed ly, GLfixed lAngle) : TexturedObject(GetVBO(buffer), T_ROCKET) 
{
  // Assign starting location
  x = lx;
  y = ly;
  angle = lAngle;
  speed = f2x(.5);

  // Mark it as a rocket
  type = OBJ_ROCKET;

  context = lContext;

  hitRadius = 4;

  smokePs = new SmokePS(context->fxMgr);

}

Rocket::~Rocket() {
  delete smokePs;
}

// Updates the rockets position, and updates it's smoke SmokeParticle system
void Rocket::Update() {

  if (speed < f2x(7))
    speed += f2x(.07);


  CalcOffset(speed, x, y);


  // Simple arena clipping
  if (x < f2x(10) || x > f2x(310))
    Die();

  if (y < f2x(10) || y > f2x(230))
    Die();

  // Make sure that the SmokeParticle system is at the same location as the rocket.
  GLfixed px = x;
  GLfixed py = y;
  CalcOffset(f2x(-10), f2x(0), px, py);
  smokePs->SetXY(px, py);
  // Update the SmokeParticle system, so that it emits a bit of smoke.
  smokePs->Update();

  GameObject *hitObj = context->objMgr->CollidesWith(this);
  if (hitObj) {
    Collision(hitObj);
    hitObj->Collision(this);
  }
}

// Called when object dies
void Rocket::Die() {
  dead = true;
  // Stop the smoke generator from outputting any more particles
  smokePs->Die();

  ExplosionPS * ps = new ExplosionPS(context->fxMgr, x, y, 2);

  context->fxMgr->Add(ps);
}

// Something hit us
void Rocket::Collision(GameObject *obj) {
  Die();
}
