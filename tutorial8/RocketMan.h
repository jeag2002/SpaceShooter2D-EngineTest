/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _ROCKET_MAN_H
#define _ROCKET_MAN_H

#include "TexturedObject.h"

#include "GameContext.h"

class RocketMan :
  public TexturedObject
{
public:
  // Contstuctor
  RocketMan(GameContext *lContext);
  ~RocketMan(void) {};

  // Performs simple AI
  void Update();

private:
  // Specifies possible states that RocketMan can be in
  enum STATE {IDLE, ATTACKING, FACING_OBJECT};
  STATE state;

  GameContext *context;

  // Max degrees to turn in one frame
  GLfixed maxAngleRate;
  GLfixed goalAngle;
  int hitPoints;

  // Shared value of how many rocketMen there are
  static int rocketManCount;

  // Counter to keep track of how long to sit idle
  int idleTime;
  // If true, charge toward player
  bool rushPlayer;

  // Number of frames to wait before firing another rocket
  int timeToFire;
  // Keeps track of which barrel the rocket is coming out of.
  GLfixed barrelOffset;
  void Fire();

  bool PointTowardGoal();
  S32BIT AngleDifference(S32BIT angle1, S32BIT angle2);
  bool PlayerIsVisible(GLfixed &pAngle, GLfixed spread);

  void EnterIdle();
  void IdleUpdate();
  void EnterFaceObject(GameObject *obj);
  void FacingUpdate();
  void EnterAttacking();
  void AttackUpdate();

  void Collision(GameObject *obj);
  void SpawnRandomly();
  void Die();

};



#endif
