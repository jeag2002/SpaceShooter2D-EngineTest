/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "input.h"

#include "wiz.h"

// Singleton class that handles storing of user input.  
// Currently very simple.  Will add other attributes as we need them.
// These values are currently set externally in an OS dependent function for Win32
// or in the Refresh method for Wiz

Input *Input::instance;

Input *Input::GetInstance() {
  if (!instance)
    instance = new Input();
  
  return(instance);
}

Input::Input(void)
{
  select = false;
  up = false;
  down = false;
  left = false;
  right = false;

  fireBtn = false;

  xChange = 0;


}

Input::~Input(void)
{
}

// Refreshes the input values
void Input::Refresh() 
{
#ifndef WIN32
  up = HW_ButtonPushed(BTN_UP);
  left = HW_ButtonPushed(BTN_LEFT);
  down = HW_ButtonPushed(BTN_DOWN);
  right = HW_ButtonPushed(BTN_RIGHT);
  fireBtn = HW_ButtonPushed(BTN_A);
  start = HW_ButtonPushed(BTN_MENU);
  select = HW_ButtonPushed(BTN_SELECT);
  volumeDown = HW_ButtonPushed(BTN_VOLDOWN);
  volumeUp = HW_ButtonPushed(BTN_VOLUP);

  if (HW_ButtonPushed(BTN_L))
    xChange = -2 << 3;
  else if (HW_ButtonPushed(BTN_R))
    xChange = 2 << 3;
  else
    xChange = 0;

#endif
}

