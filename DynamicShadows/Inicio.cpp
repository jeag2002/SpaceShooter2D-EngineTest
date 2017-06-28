#include <windows.h>

#include "AllInclude.h"


int main (int argc, char *argv[])
{
	SDL_Event event;

	Uint8* keyStates;

	bool quit = false;
	
	// Frame rate control
	FPSTimer fpsTimer;
	const int framesPerSecond = 60;
	int frameTime = 1000/framesPerSecond;

	// ---------------------------- Initialize SDLOpenGL ---------------------------

	// Must set before initializing
	window_width = 1000;
	window_height = 800;

	const float half_window_width = window_width/2.0f;
	const float half_window_height = window_height/2.0f;

	if(!InitSDLOpenGL())
	{
		/*MessageBox(NULL,"Could not initialize SDLOpenGL",
			"ERROR",MB_OK|MB_ICONEXCLAMATION);*/
		exit(-1);
	}

	// ---------------------------- Set up OpenGL for 2D ---------------------------

	// SDLOpenGL defaults to perspective, change to ortho
	ViewOrtho(-1.0f, 100.0f);

	// ---------------------------- Lighting System ----------------------------

	LightSystem lightSystem;

	Light testLight;
	testLight.radius = 400.0f;
	testLight.center.x = half_window_width;
	testLight.center.y = half_window_height;
	lightSystem.addLight(&testLight);

	ConvexHull testHull;

	if(!testHull.LoadShape("testShape.txt"))
	{
		/*MessageBox(NULL,"Could not load shape",
			"ERROR",MB_OK|MB_ICONEXCLAMATION);*/

		QuitSDLOpenGL();
		
		exit(-1);
	}

	testHull.worldCenter.x = half_window_width;
	testHull.worldCenter.y = half_window_height;

	lightSystem.addConvexHull(&testHull);

	// ----------------------------- Load Resources ----------------------------

	TextureDesc floor;
	LoadIMG("floor1.bmp", floor);

	TextureDesc testImage;
	LoadIMG("testImage.bmp", testImage);

	// ------------------------------- Game Loop -------------------------------

	while(!quit)
	{
		// Start the frame timer
        fpsTimer.start();

		while(SDL_PollEvent( &event ))
		{
			// Two ways to quit: x button and escape key
			if(event.type == SDL_QUIT)
                quit = true;

			if(event.type == SDL_MOUSEMOTION)
			{
				testLight.center.x = static_cast<float>(event.motion.x);
				testLight.center.y = static_cast<float>(window_height - event.motion.y);
			}
		}

		keyStates = SDL_GetKeyState(NULL);

		if(keyStates[27])
			quit = true;

		// -------------------------------------- Game Step ---------------------------------------

		// Clear screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		lightSystem.RenderLights();

		// Render background
		glTranslatef(half_window_width, half_window_height, 0.0f);
		glScalef(4.0f, 4.0f, 1.0f);
		Draw2DQuad(floor, 4.0f);

		// Render test image
		glLoadIdentity();
		glTranslatef(half_window_width, half_window_height, 0.0f);
		Draw2DQuad(testImage, 1.0f);

		// Update screen
		SDL_GL_SwapBuffers();

		// ---------------------------------- Frame Rate Control ----------------------------------

		// Cap the frame rate
		fpsTimer.capFrameRate(framesPerSecond);

		frameTime = fpsTimer.get_ticks(); // For frame independent movement
	}

	// ---------------------------------- Clean Up ----------------------------------

	QuitSDLOpenGL();

	return 0;
}


/*
undefined reference to `_WinMain@16'
http://www.daniweb.com/software-development/cpp/threads/92830
http://www.allegro.cc/forums/thread/596872
http://forums.codeblocks.org/index.php?topic=7580.0
*/


/*

||=== DynamicShadows, host ===|
C:\Program Files\GPH_SDK\DGE\include\GL\glu.h|51|warning: "GLAPI" redefined|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\include\GL\gl.h|61|warning: this is the location of the previous definition|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|36|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\ConvexHull.cpp||In member function `Point2f ConvexHull::getWorldVertex(unsigned int)':|
C:\Workspaces\CodeBlocks\DynamicShadows\ConvexHull.cpp|62|warning: comparison of unsigned expression >= 0 is always true|
C:\Workspaces\CodeBlocks\DynamicShadows\ConvexHull.cpp|96|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h||In function `T Wrap(T, T) [with T = unsigned int]':|
C:\Workspaces\CodeBlocks\DynamicShadows\ConvexHull.cpp|73|instantiated from here|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|27|warning: comparison of unsigned expression < 0 is always false|
C:\Workspaces\CodeBlocks\DynamicShadows\FPSTimer.h|40|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\FPSTimer.cpp|103|warning: no newline at end of file|
C:\Program Files\GPH_SDK\DGE\include\GL\glu.h|51|warning: "GLAPI" redefined|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\include\GL\gl.h|61|warning: this is the location of the previous definition|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.h|37|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|36|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h|24|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\FPSTimer.h|40|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\AllInclude.h|14|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Inicio.cpp|7|warning: unused parameter 'argc'|
C:\Workspaces\CodeBlocks\DynamicShadows\Inicio.cpp|7|warning: unused parameter 'argv'|
C:\Workspaces\CodeBlocks\DynamicShadows\Inicio.cpp|142|warning: no newline at end of file|
C:\Program Files\GPH_SDK\DGE\include\GL\glu.h|51|warning: "GLAPI" redefined|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\include\GL\gl.h|61|warning: this is the location of the previous definition|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.h|37|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|36|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h|24|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h||In constructor `Light::Light()':|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h|16|warning: `Light::depth' will be initialized after|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h|15|warning:   `Vec2f Light::center'|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.cpp|13|warning:   when initialized here|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.cpp|41|warning: no newline at end of file|
C:\Program Files\GPH_SDK\DGE\include\GL\glu.h|51|warning: "GLAPI" redefined|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\include\GL\gl.h|61|warning: this is the location of the previous definition|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.h|37|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|36|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Light.h|24|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\LightSystem.cpp|184|warning: no newline at end of file|
C:\Program Files\GPH_SDK\DGE\include\GL\glu.h|51|warning: "GLAPI" redefined|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\include\GL\gl.h|61|warning: this is the location of the previous definition|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.h|37|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|11|warning: converting to non-pointer type `Uint32' from NULL|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp||In function `SDL_Surface* ConvertToRGBA(SDL_Surface*)':|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|86|warning: comparison between signed and unsigned integer expressions|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|88|warning: comparison between signed and unsigned integer expressions|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|89|warning: unused variable 'id'|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|133|warning: comparison between signed and unsigned integer expressions|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|135|warning: comparison between signed and unsigned integer expressions|
C:\Workspaces\CodeBlocks\DynamicShadows\SDLOpenGL.cpp|330|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.h|36|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Utilities.cpp|64|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.h|126|warning: no newline at end of file|
C:\Workspaces\CodeBlocks\DynamicShadows\Constructs.cpp|330|warning: no newline at end of file|
C:\CodeBlocks-8.02\MinGW\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\libmingw32.a(main.o):main.c|| first defined here|
||Warning: .drectve `/manifestdependency:"type='win32' name='Microsoft.VC90.CRT' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'" /DEFAULTLIB:"MSVCRT" /DEFAULTLIB:"OLDNAMES" ' unrecognized|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_main]+0x7)||undefined reference to `___security_cookie'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_main]+0x99)||undefined reference to `__alloca_probe_16'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_main]+0x14e)||undefined reference to `@__security_check_cookie@4'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_ShowError]+0x12)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_cleanup_output]+0x8)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_cleanup_output]+0x1b)||undefined reference to `__imp____iob_func'|
16]+0x7)||undefined reference to `___security_cookie'|
16]+0x80)||undefined reference to `__alloca_probe_16'|
16]+0xca)||undefined reference to `__alloca_probe_16'|
16]+0x10f)||undefined reference to `@__security_check_cookie@4'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0xa)||undefined reference to `___security_cookie'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0x8a)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0xcf)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0x111)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0x156)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0x171)||undefined reference to `__imp____iob_func'|
C:\SDL-1.2.15\lib\SDLmain.lib(.\Release\SDL_win32_main.obj):(.text[_redirect_output]+0x1a9)||undefined reference to `@__security_check_cookie@4'|
||=== Build finished: 18 errors, 53 warnings ===|




*/