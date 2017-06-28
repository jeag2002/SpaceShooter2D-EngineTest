/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _FIXED_TRIG_H
#define _FIXED_TRIG_H

#include "defines.h"

class FixedTrig
{
public:
  // Get singleton instance
  static FixedTrig *GetInstance(void);

  ~FixedTrig(void);

  // Returns the cosine of the passed in angle.  Angle is in degrees.
  S32BIT Cosx(S32BIT angle);

  // Returns the sine of the passed in angle.  Or maybe it's a cold medicine.  Angle is in degrees.
  S32BIT Sinx(S32BIT angle);

  // Returns the arc tangent for the given coords via the Cordic method
  S32BIT Atan2Cordic(int x, int y);

private:
  FixedTrig(void);
  static FixedTrig *instance;

  S32BIT *luTable;

  void BuildLookupTable();

  S32BIT GetTableValue(S32BIT angle);
};

#endif
