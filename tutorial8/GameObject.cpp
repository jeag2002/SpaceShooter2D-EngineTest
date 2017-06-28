/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "GameObject.h"
#include "FixedTrig.h"

GameObject::GameObject(void) : dead(false), x(0), y(0), type(OBJ_NONE), angle(0), hitRadius(0) 
{
  fixedTrig = FixedTrig::GetInstance();
}

// Uses object's angle and passed in x and y values to calculate offset
void GameObject::CalcOffset(GLfixed dist, GLfixed &lx, GLfixed &ly) {
  ly += ((dist >> 8) * fixedTrig->Sinx(angle)) >> 8;

  lx += ((dist >> 8) * fixedTrig->Cosx(angle)) >> 8;
}

// Uses object's angle and passed in x and y values to calculate offset
void GameObject::CalcOffset(GLfixed xDist, GLfixed yDist, GLfixed &lx, GLfixed &ly) {

  lx += (((xDist >> 8) * fixedTrig->Cosx(angle)) >> 8) - 
        (((yDist >> 8) * fixedTrig->Sinx(angle)) >> 8);

  ly += (((xDist >> 8) * fixedTrig->Sinx(angle)) >> 8) + 
        (((yDist >> 8) * fixedTrig->Cosx(angle)) >> 8);

}
