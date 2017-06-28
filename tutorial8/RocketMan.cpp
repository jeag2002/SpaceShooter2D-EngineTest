/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "RocketMan.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "rocket.h"
#include "fixedtrig.h"
#include "ExplosionPS.h"
#include "Arena.h"
#include "Player.h"
#include "VBOAllocator.h"

int RocketMan::rocketManCount = 1;

// How far we can see to the left and right.  80 = 160 degrees of vision
#define VIEWING_ANGLE f2x(80)
// How close to pointing toward our goal we have to be before we fire.
#define SHOOTING_ANGLE f2x(15)

#define MOVEMENT_SPEED f2x(.75)
#define TURNING_SPEED f2x(1)

// Define a 16 x 16 square for the RocketMan
// Orientated so that the center of the rectangle is near the center of the enemy
static  GLfixed buffer[] = {
  	f2x(-15.5), f2x(-15.5),f2x(0.0f), f2x(0.0f),
	  f2x(15.5),  f2x(-15.5),f2x(1.0f), f2x(0.0f),
	  f2x(-15.5), f2x(15.5),f2x(0.0f), f2x(1.0f),
	  f2x(15.5),  f2x(15.5),f2x(1.0f), f2x(1.0f)
  };


// We need a fxMgr since when we spawn a rocket we need to pass one in.  There's probably a better pattern to use here.
RocketMan::RocketMan(GameContext *lContext) : TexturedObject(GetVBO(buffer), T_ROCKETMAN)
{
  context = lContext;

  type = OBJ_ROCKETMAN;

  timeToFire = 0;
  barrelOffset = f2x(-12);
  hitRadius = 16;

  angle = f2x(45);
  goalAngle = f2x(45);

  // Start out in Idle mode
  EnterIdle();

  maxAngleRate = TURNING_SPEED;

  hitPoints = 10;
}


S32BIT RocketMan::AngleDifference(S32BIT angle1, S32BIT angle2) {
  S32BIT smallAngle;
  S32BIT largeAngle;

  if (angle1 < angle2) {
    smallAngle = angle1;
    largeAngle = angle2;
  } else {
    smallAngle = angle2;
    largeAngle = angle1;
  }

  S32BIT opt1 = largeAngle - smallAngle;
  S32BIT opt2 = (smallAngle + f2x(360)) - largeAngle;

  if (opt1 < opt2)
    return opt1;
  else
    return opt2;
}


bool RocketMan::PlayerIsVisible(GLfixed &pAngle, GLfixed spread) {

  GameObject *player = context->objMgr->GetPlayer();
  if (player == NULL) {
    return false;
  }

  S32BIT dx = player->GetX() - GetX();
  S32BIT dy = player->GetY() - GetY();
  S32BIT playerAngle = FixedTrig::GetInstance()->Atan2Cordic(dx, dy);

  if (AngleDifference(playerAngle, angle) < spread) {
    pAngle = playerAngle;
    return true;
  }

  return false;

  GLfixed diff = (abs(angle - playerAngle) >> 16);

  // If we can see the player, return true
  if (abs(angle - playerAngle) < spread) {
    pAngle = playerAngle;
    return true;
  }

  return false;
}

void RocketMan::EnterIdle() {

  state = IDLE;

  idleTime = (rand() % 180) + 60;

  // Usually if we get here, goalAngle is where we last saw player, so keep it as a goal angle if we haven't hit it yet
  if (goalAngle == angle) {

    int choice = rand() % 6;

    switch (choice) {
      // Point toward the center of the arena
      case 0:
        goalAngle = angle + f2x((rand() % 45) - 22);
        break;
      // Flip 180 degrees
      case 1:
        goalAngle = angle + f2x(180);
        break;
      // Pick a random place to point
      case 2:
        goalAngle = angle + f2x(rand() % 360);
        break;
      // Just look around a little
      default:
        goalAngle = FixedTrig::GetInstance()->Atan2Cordic(f2x(ARENA_WIDTH / 2), f2x(ARENA_HEIGHT / 2));
        break;
    }

    if (goalAngle < 0)
      goalAngle += f2x(360);
    else if (goalAngle > f2x(360))
      goalAngle -= f2x(360);
  }
}

void RocketMan::IdleUpdate()
{
  if (PlayerIsVisible(goalAngle, VIEWING_ANGLE)) {
    EnterAttacking();
    return;
  }

  if (PointTowardGoal()) {
    if (idleTime)
      idleTime--;
    else
    {
      // Pick something else to do
      EnterIdle();
    }
  }
}

bool RocketMan::PointTowardGoal() {
  bool addDelta = true;

  // Try to point toward our goal angle
  if (goalAngle != angle) {
    GLfixed delta = goalAngle - angle;
    if (delta < 0) {
      addDelta = false;
      delta = -delta;
    }

   if (delta > f2x(180)) {
     delta = f2x(360) - delta;
     addDelta = !addDelta;
   }

    if (delta > maxAngleRate)
      delta = maxAngleRate;

    if (addDelta)
      angle += delta;
    else
      angle -= delta;

    if (angle >= f2x(360))
      angle -= f2x(360);
    else if (angle < 0)
      angle += f2x(360);

    return false;
  }
  return true;
}

void RocketMan::EnterAttacking() {

  state = ATTACKING;

  // Represents how long we stay in this attack mode (rushing vs non rushing)
  idleTime = (rand() % 120) + 120;

  if (rand() % 2)
    rushPlayer = true;
  else
    rushPlayer = false;
}

void RocketMan::AttackUpdate()
{
  if (idleTime)
    idleTime--;
  else
    // Switch up standing still or rushing
    EnterAttacking();

  if (PlayerIsVisible(goalAngle, VIEWING_ANGLE)) {
    if (rushPlayer)
      // Move forward a bit
      CalcOffset(MOVEMENT_SPEED, x, y);

    PointTowardGoal();


    if (PlayerIsVisible(goalAngle, SHOOTING_ANGLE))
      Fire();
  }
  else
    EnterIdle();


}

void RocketMan::EnterFaceObject(GameObject *obj) {

  state = FACING_OBJECT;

  S32BIT dx = obj->GetX() - GetX();
  S32BIT dy = obj->GetY() - GetY();
  goalAngle = FixedTrig::GetInstance()->Atan2Cordic(dx, dy);
  if (goalAngle < 0)
    goalAngle += f2x(360);
  else if (goalAngle > f2x(360))
    goalAngle -= f2x(360);

  idleTime = (rand() % 60) + 60;
}

void RocketMan::FacingUpdate()
{
  PointTowardGoal();

  if (PlayerIsVisible(goalAngle, VIEWING_ANGLE)) {
    EnterAttacking();
  }

  if (goalAngle == angle) {
    if (idleTime == 0)
      EnterIdle();
    else
      idleTime--;
  }

}


// Circles around, firing rockets when possible
void RocketMan::Update() {

  if (timeToFire)
    timeToFire--;

  // Store our original locations
  GLfixed ox = x;
  GLfixed oy = y;

  switch (state)
  {
  case IDLE:
    IdleUpdate();
    break;
  case ATTACKING:
    AttackUpdate();
    break;
  case FACING_OBJECT:
    FacingUpdate();
    break;
  }

  GameObject *hitObj = context->objMgr->CollidesWith(this);
  if (hitObj) {
    Collision(hitObj);
    // We hit something, move us back to where we were
    x = ox;
    y = oy;

    hitObj->Collision(this);
  }
}

void RocketMan::Fire()
{
  if (timeToFire)
    return;

  // Offset the rocket so it looks like it's comming out of one of the launchers
  if (barrelOffset == f2x(-12))
    barrelOffset = f2x(12);
  else
    barrelOffset = f2x(-12);

  timeToFire = 60;
  GLfixed lx = x;
  GLfixed ly = y;
  CalcOffset(f2x(23), barrelOffset, lx, ly);
  context->objMgr->Add(new Rocket(context, lx, ly, angle));

}

  // Gets called when something else hits this object
void RocketMan::Collision(GameObject *obj){

  if (obj->GetType() == OBJ_BULLET) {
    hitPoints--;
    context->AddToScore(1);

    if (state == IDLE)
      EnterFaceObject(obj);
  } else if (obj->GetType() == OBJ_ROCKET) {
    hitPoints -= 5;
    if (state == IDLE)
      EnterFaceObject(obj);
  } else if (obj->GetType() == OBJ_PLAYER) {
    if (state != ATTACKING)
      EnterFaceObject(obj);
  }

  if (hitPoints <= 0)
    Die();

};

// Add a new rocket man to a random spot in the map
void RocketMan::SpawnRandomly() {

  if (rocketManCount >= 5)
    return;

  RocketMan *newBoss = new RocketMan(context);

  // Only try to add this guy x times.  If we can't find a spot, give up.
  for (int i = 0; i < 10; i++) {
    GLfixed tempX = f2x((rand() % 280) + 20);
    GLfixed tempY = f2x((rand() % 200) + 20);
    newBoss->SetXY(tempX, tempY);

    if (context->objMgr->CollidesWith(newBoss) == NULL) {
      context->objMgr->Add(newBoss);
      rocketManCount++;
      return;
    }
  }

  delete newBoss;
}

void RocketMan::Die() {
  dead = true;

  ExplosionPS * ps = new ExplosionPS(context->fxMgr, x, y, 4);

  context->fxMgr->Add(ps);

  rocketManCount --;

  // Every time one dies, two new rocketmen pop up randomly.
  SpawnRandomly();
  SpawnRandomly();

};

