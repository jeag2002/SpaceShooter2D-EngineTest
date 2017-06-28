/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

// Class that hides GL / GL|ES initialization and termination from main app.
// Heavily based off of PowerVR "Training Course" 01_Initialization tutorial.

#include "glcontrol.h"

#ifdef WIN32
  #include <tchar.h>
#else
extern "C" {
  NativeWindowType OS_CreateWindow();
}

#endif

#include <iostream>
#include "input.h"
#include "defines.h"
#include "text.h"

using namespace std;

#ifdef WIN32

// Window title and class name.  These are OS specific, not useful for other platforms.
#define WINDOW_TITLE _T("tutorial8")
#define WINDOW_CLASSNAME _T("tutorialWin")

// Minimal WndProc function that handles closing the window and catching the Escape key.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static int lastMouse = 0;
	switch (message)
	{
    case WM_MOUSEMOVE:
      if (wParam == MK_LBUTTON)
        Input::GetInstance()->fireBtn = true;
      else
        Input::GetInstance()->fireBtn = false;
      return 0;

		// User clicked the close button
		case WM_CLOSE:
      Input::GetInstance()->select = true;
			PostQuitMessage(0);
			return 1;
  	case WM_KEYDOWN:
    	{
		  switch(wParam)
		    {
		    // User pressed the Escape key
		    case VK_ESCAPE:
          Input::GetInstance()->select = true;
    			break;
		    case 'W':
          Input::GetInstance()->up = true;
    			break;
		    case 'S':
          Input::GetInstance()->down = true;
    			break;
		    case 'D':
          Input::GetInstance()->right = true;
    			break;
		    case 'A':
          Input::GetInstance()->left = true;
    			break;
    		}
      }
      return 0;
  	case WM_KEYUP:
    	{
		  switch(wParam)
		    {
		    // User pressed the Escape key
		    case VK_ESCAPE:
          Input::GetInstance()->select = false;
    			break;
		    case 'W':
          Input::GetInstance()->up = false;
    			break;
		    case 'S':
          Input::GetInstance()->down = false;
    			break;
		    case 'D':
          Input::GetInstance()->right = false;
    			break;
		    case 'A':
          Input::GetInstance()->left = false;
    			break;
    		}
      }
      return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif

// Empty constructor
GLControl::GLControl(void)
{

#ifdef WIN32
  // Initialize the mouse reading vars
  window_center_x = WINDOW_WIDTH / 2;
  window_center_y = WINDOW_HEIGHT / 2;

  // the two 0 values disable the two acceleration thresholds, and the
  // 1 value specifies medium mouse speed
  newmouseparms[0] = 0;
  newmouseparms[0] = 0;
  newmouseparms[0] = 1;

  mouse_x_accum = 0;
  mouse_y_accum = 0;
#endif
}


// Trivial destructor
GLControl::~GLControl(void)
{
}

// Initializes this class and OpenGL
#ifdef WIN32
bool GLControl::Init(HINSTANCE hInstance)
{
  // Set member variables to decent initial values
  display = NULL;
  surface = NULL;
  hWnd = NULL;
  hDC = NULL;
	// Register the windows class
	WNDCLASS sWC;
  sWC.style = CS_HREDRAW | CS_VREDRAW;
  sWC.lpfnWndProc = WndProc;
  sWC.cbClsExtra = 0;
  sWC.cbWndExtra = 0;
  sWC.hInstance = hInstance;
  sWC.hIcon = 0;
  sWC.hCursor = 0;
  sWC.lpszMenuName = 0;
  sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
  sWC.lpszClassName = WINDOW_CLASSNAME;
    
	ATOM registerClass = RegisterClass(&sWC);
	if (!registerClass)
	{
    cout << "Failed to register the window class" << endl;
		return false;
	}

	// Create a native OS window
	RECT	sRect;
	SetRect(&sRect, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
	hWnd = CreateWindow( WINDOW_CLASSNAME, WINDOW_TITLE, WS_VISIBLE | WS_SYSMENU,
						 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
						 
	NativeWindowType	eglWindow	= hWnd;

	// Get the associated device context
	hDC = GetDC(hWnd);
	if (!hDC)
	{
    cout << "Failed to create the device context" << endl;
		return false;
	}

  display = eglGetDisplay((NativeDisplayType)hDC);
  if(display == EGL_NO_DISPLAY)
    display = eglGetDisplay((NativeDisplayType) EGL_DEFAULT_DISPLAY);
	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(display, &iMajorVersion, &iMinorVersion))
	{
    cout << "eglInitialize() failed." << endl;
		return false;
	}

  // Set up configuration attributes for OpenGL ES.
	int i = 0;
	EGLint				pi32ConfigAttribs[128];
	pi32ConfigAttribs[i++] = EGL_RED_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_GREEN_SIZE;
	pi32ConfigAttribs[i++] = 6;
	pi32ConfigAttribs[i++] = EGL_BLUE_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_ALPHA_SIZE;
	pi32ConfigAttribs[i++] = 0;
	pi32ConfigAttribs[i++] = EGL_SURFACE_TYPE;
	pi32ConfigAttribs[i++] = EGL_WINDOW_BIT;
	pi32ConfigAttribs[i++] = EGL_NONE;

  // Get a configuration that matches our attributes.  This should return one matching configuration
	EGLConfig			config	= NULL;
	int iConfigs;
	if (!eglChooseConfig(display, pi32ConfigAttribs, &config, 1, &iConfigs) || (iConfigs != 1))
	{
    cout << "eglChooseConfig() failed." << endl;
		return false;
	}
  

  // Creates a window surface.  This represents the onscreen client area of our window
  surface = NULL;
	surface = eglCreateWindowSurface(display, config, eglWindow, NULL);
	
  if(surface == EGL_NO_SURFACE)
  {
    eglGetError(); // Clear error
    surface = eglCreateWindowSurface(display, config, NULL, NULL);
	}

	if (!CheckError("eglCreateWindowSurface"))
	{
    cout << "Failed to create window surface." << endl;
		return false;
	}

  // Creates a context.  I'm not too clear on it's purpose yet.
	EGLContext  context;
	context = eglCreateContext(display, config, NULL, NULL);
	if (!CheckError("eglCreateContext"))
	{
	  cout << "Failed to CreateContext." << endl;
		return false;
	}

  // Associates our diplay and surface with the context, and makes the context current.
	eglMakeCurrent(display, surface, surface, context);
	if (!CheckError("eglMakeCurrent"))
	{
	  cout << "Failed to bind context to thread." << endl;
		return false;
	}

  StartGameMouse();

#else
EGLint attrib_list[] =
{
  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  EGL_BUFFER_SIZE,  0,
  EGL_RED_SIZE, 5,
  EGL_GREEN_SIZE, 6,
  EGL_BLUE_SIZE, 5,
  EGL_ALPHA_SIZE, 0,
  EGL_DEPTH_SIZE,   16,
  EGL_NONE
};

bool GLControl::Init()
{
  EGLConfig       glConfig;
  EGLContext      glContext;


  NativeWindowType hNativeWnd = 0;
  hNativeWnd = OS_CreateWindow();
  display = eglGetDisplay( (NativeDisplayType)0 );

  EGLint majorVersion;
  EGLint minorVersion;
  eglInitialize( display, &majorVersion, &minorVersion);

  EGLint numConfigs;
  eglChooseConfig( display, attrib_list, &glConfig, 1, &numConfigs);

  glContext = eglCreateContext( display, glConfig, NULL, NULL );
  surface = eglCreateWindowSurface( display, glConfig, hNativeWnd, NULL );
  eglMakeCurrent( display, surface, surface, glContext );    

#endif


  // Place the matrix mode into Projection mode.
  glMatrixMode(GL_PROJECTION);
  // Set up our view
  glOrthox(f2x(0), f2x(320), f2x(0), f2x(240), f2x(-1), f2x(1));

  // Get ready for our model manipulations
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Turn on blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);    	
  

  AllocateTextBuffers();

  // Return true, all success.
  return true;
}


// Clean up egl and OS specific objects
void GLControl::Term(void)
{
	FreeTextBuffers();

  // Clean up OpenGL|ES specific entities.  These handles sub-entities as well.
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(display);

#ifdef WIN32
  StopGameMouse();

	// Release the device context
	if (hDC) 
	  ReleaseDC(hWnd, hDC);

	// Destroy the OS window
	if (hWnd) 
	  DestroyWindow(hWnd);
#endif
}

// Helper function that checks the last error.  If false, it outputs a semi-helpful message
bool GLControl::CheckError(char* pszLocation)
{
	EGLint err = eglGetError();
	if (err != EGL_SUCCESS)
	{
		cout << pszLocation << " failed (" << err << ")." << endl;
		return false;
	}

	return true;
}

// Displays rendered scene and does some message handling
void GLControl::Pump(void) {

    // Displays rendered content.  Double buffered?
  eglSwapBuffers(display, surface);

#ifdef WIN32
  // Managing the window messages
  MSG msg;

  while ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
  { 
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  AccumulateGameMouseMove();
  int dummyX, dummyY;

  GetGameMouseMoveForFrame (&dummyX, &dummyY);
  Input::GetInstance()->xChange = dummyX;
#endif
}


#ifdef WIN32
// functions to start up and shutdown the game configuration for
// the mouse, and to accumulate mouse moves over multiple calls
// during a frame and to calculate the total move for the frame


int GLControl::StartGameMouse (void)
{
   if (!SystemParametersInfo (SPI_GETMOUSE, 0, originalmouseparms, 0))
      return 0;
   if (!SystemParametersInfo (SPI_SETMOUSE, 0, newmouseparms, 0))
      return 0;
   ShowCursor (FALSE);
   SetCursorPos (window_center_x, window_center_y);
   return 1;
}
void GLControl::StopGameMouse (void)
{
   SystemParametersInfo (SPI_SETMOUSE, 0, originalmouseparms, 0);
   ShowCursor (TRUE);
}
void GLControl::AccumulateGameMouseMove (void)
{
   GetCursorPos (&current_pos);

   mouse_x_accum += current_pos.x - window_center_x;
   mouse_y_accum += current_pos.y - window_center_y;

   // force the mouse to the center, so there's room to move
   SetCursorPos (window_center_x, window_center_y);
}
void GLControl::GetGameMouseMoveForFrame (int * mouse_x_move, int * mouse_y_move)
{
   GetCursorPos (&current_pos);
   *mouse_x_move = current_pos.x - window_center_x + mouse_x_accum;
   *mouse_y_move = current_pos.y - window_center_y + mouse_y_accum;
   mouse_x_accum = 0;
   mouse_y_accum = 0;

   // force the mouse to the center, so there's room to move
   SetCursorPos (window_center_x, window_center_y);
}

#endif

