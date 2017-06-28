/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "defines.h"

#include <GLES/gl.h>
#include "ObjectTypes.h"
#include "FixedTrig.h"

// Defines a generic non-instantiable game object.
// More complex game objects are built off of this one.
class GameObject
{
public:
  // Constructor, initializes member variables
  GameObject(void);
  virtual ~GameObject(void) {};
  // Abstract virtual function, children classes must define this in order to be instantiated
  virtual void Update() = 0;
  // Abstract virtual function, children classes must define this in order to be instantiated
  virtual void Draw() = 0;

  // Marks the item as dead.  Can be overridden.
  virtual void Die() {dead = true;};

  // Positional methods.  Trivially implemented.  If these need to be overridden, be sure to make these virtual
  GLfixed GetX() {return x;};
  GLfixed GetY() {return y;};
  int GetHitRadius() {return hitRadius;};
  void SetX(GLfixed lx) {x = lx;};
  void SetY(GLfixed ly) {y = ly;};
  void SetXY(GLfixed lx, GLfixed ly) {x = lx; y = ly;};

  // Angle manipulation.  Trivially implemented.
  GLfixed GetAngle() {return angle;};
  void SetAngle(GLfixed lAngle) {angle = lAngle;};

  // Returns true if this object is considered dead.  Usefull for culling from lists.
  bool IsDead() {return dead;};

  // Returns the type of object this.  Faster than reflection.
  ObjectType GetType() {return type;};

  // Gets called when something else hits this object
  virtual void Collision(GameObject *obj) {};

  // Helper function that calculates an offest along the direction the object is facing.
  // positive Y offsets move forward the direction the object is facing,
  // positive X offsets are to the right of the direction that the object is facing.
  void CalcOffset(GLfixed dist, GLfixed &lx, GLfixed &ly);
  void CalcOffset(GLfixed xDist, GLfixed yDist, GLfixed &lx, GLfixed &ly);


protected:
  bool dead;
  GLfixed x;
  GLfixed y;

  ObjectType type;
  GLfixed angle;
  int hitRadius;

  // Saved for ease of access
  FixedTrig *fixedTrig;
};


#endif
