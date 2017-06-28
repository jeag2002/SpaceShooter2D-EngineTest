/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef GL_CONTROL_H
#define GL_CONTROL_H

#include <GLES/egl.h>
#include <GLES/gl.h>

// Class that hides GL / GL|ES initialization and termination from main app.
// Heavily based off of PowerVR "Training Course" 01_Initialization tutorial.
class GLControl
{
public:
  GLControl(void);
  ~GLControl(void);

  // Initialize the OpenGL system, creating an appropriate window
#ifdef WIN32
  bool Init(HINSTANCE hInstance);
#else
  bool Init();
#endif

  // Close the OpenGL system, cleaning up any related resources
  void Term(void);
  // Display the scene, and do any appropriate OS related per-frame work necessary.
  void Pump(void);
  
private:  
  EGLDisplay display;
  EGLSurface surface;

#ifdef WIN32
  HWND hWnd;
  HDC hDC;

  // Note that these mouse reading functions were borrowed from 
  // Micahel Abrash's article on Win32 game programming :
  // http://www.ddj.com/architect/184410376
  // (I remember reading this over 10 years ago, it's fairly bizarre running across it again.  
  //  I always enjoyed Michael Abrash's writing style, I wonder what he's up to nowadays.)
  int window_center_x;
  int window_center_y;

  int     originalmouseparms[3], newmouseparms[3];
  int     mouse_x_accum, mouse_y_accum;
  POINT   current_pos;

  int StartGameMouse (void);
  void StopGameMouse (void);
  void AccumulateGameMouseMove (void);
  void GetGameMouseMoveForFrame (int * mouse_x_move, int * mouse_y_move);

#endif

  bool CheckError(char* pszLocation);

};

#endif
