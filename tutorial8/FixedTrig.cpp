/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "FixedTrig.h"

#include <stdlib.h>
#include <math.h>

#define TABLE_SIZE 1024

FixedTrig *FixedTrig::instance = NULL;

FixedTrig::FixedTrig(void)
{
  luTable = NULL;
  BuildLookupTable();
}

void FixedTrig::BuildLookupTable() {
  luTable = new S32BIT[TABLE_SIZE];

  if (!luTable)
    return;

  // We're going to keep track of 90 degrees of sine.
  float angleOffset = 90.0f / TABLE_SIZE;

  for (int i = 0 ; i < TABLE_SIZE; i++) {
    // We're doing this in degrees instead of radians since OpenGL uses degrees
    luTable[i] = (S32BIT)((sinf((float)i * angleOffset / (180.0f / 3.14159f))) * 65536.0f);

  }

}

// The passed in angle should always be between 0 and 90 degrees fixed point.
S32BIT FixedTrig::GetTableValue(S32BIT angle) {
  if (luTable) {
    // We need to take our 0 to 90 value, and resolve it to 1024 possible values
    // angle / 90 * 1024
    // == angle * (1024 / 90)

    // Broken out for debugging / clarity
    S32BIT temp = (TABLE_SIZE << 8) / 90;

    S32BIT index = ((angle >> 4) * temp) >> 20;

    S32BIT retVal = luTable[index];

    return retVal;
  } else
    return 0;
}

// Returns the sine of the passed in angle.  Or maybe it's a cold medicine.
S32BIT FixedTrig::Sinx(S32BIT angle) {

  S32BIT lAngle = angle % f2x(360);
  if (lAngle < 0)
    lAngle += f2x(360);

  // Do a look up based on which quadrant the angle is in
  if (lAngle > f2x(270)) 
    return -GetTableValue(f2x(360) - lAngle);
  else if (lAngle > f2x(180)) 
    return -GetTableValue(lAngle - f2x(180));
  else if (lAngle > f2x(90)) 
    return GetTableValue(f2x(180) - lAngle);
  else 
    return GetTableValue(lAngle);
  
}

// Returns the cosine of the passed in angle
S32BIT FixedTrig::Cosx(S32BIT angle) {
  return (Sinx(angle + f2x(90)));
}

// atan via CORDIC (coordinate rotations).
// Returns f2x(0 thru 360)
S32BIT FixedTrig::Atan2Cordic(int x, int y)
{
    if (y == 0)    
      return (x >= 0 ? f2x(0) : f2x(180));

    // Move x & y into proper octant
    int _t; 
    int phi = 0;
    if(y < 0) {            
      x= -x;   
      y= -y; 
      phi += 4; 
    }
    if(x <= 0) { 
      _t= x;    
      x=  y;   
      y= -_t; 
      phi += 2; 
    }

    if (x <= y)  { 
      _t = y - x; 
      x = x + y; 
      y =  _t; 
      phi += 1; 
    }

    phi = f2x(phi * (180 / 4));

    // atan(2^-i) terms using PI=0x10000 for accuracy
    const U16BIT list[]=
    {
        0x4000, 0x25C8, 0x13F6, 0x0A22, 0x0516, 0x028C, 0x0146, 0x00A3,
        0x0051, 0x0029, 0x0014, 0x000A, 0x0005, 0x0003, 0x0001, 0x0001
    };

    int i, tmp, dphi=0;
    for(i=1; i<12; i++)
    {
        if(y>=0)
        {
            tmp= x + (y>>i);
            y  = y - (x>>i);
            x  = tmp;
            dphi += list[i];
        }
        else
        {
            tmp= x - (y>>i);
            y  = y + (x>>i);
            x  = tmp;
            dphi -= list[i];
        }
    }
    S32BIT retVal = phi + ((float)(dphi / 65536.0f) * f2x(180));

    return retVal;
}

FixedTrig::~FixedTrig(void)
{
  if (luTable)
    delete [] luTable;
}


// Allows access to single instance
FixedTrig *FixedTrig::GetInstance(void) {

  if (instance == NULL) 
    instance = new FixedTrig();
  
 return(instance);
}
