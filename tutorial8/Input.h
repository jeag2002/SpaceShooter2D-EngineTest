/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _INPUT_H
#define _INPUT_H

// Singleton class that handles storing of user input.  
// Contains properties the reflect various input states.
// Allows seperation of input hardware from input readers.
class Input
{
public:
  static Input *GetInstance();
  ~Input(void);

  void Refresh();

  bool select;  // WIN32: Mapped to Esc
  bool left;    // WIN32: Mapped to A
  bool right;   // WIN32: Mapped to D
  bool down;    // WIN32: Mapped to W
  bool up;      // WIN32: Mapped to S

  bool volumeUp;
  bool volumeDown;
  bool start;

  bool fireBtn; // Mapped to left mouse button

  // Delta value for mouse our joystick across X axis
  int xChange;

protected:
  Input(void);
  static Input *instance;

};

#endif
