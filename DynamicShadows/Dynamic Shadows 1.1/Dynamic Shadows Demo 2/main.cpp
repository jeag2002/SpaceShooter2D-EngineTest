#include "AllInclude.h"

int main(int argc, char* argv[])
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
		MessageBox(NULL,"Could not initialize SDLOpenGL",
			"ERROR",MB_OK|MB_ICONEXCLAMATION);
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
		MessageBox(NULL,"Could not load shape",
			"ERROR",MB_OK|MB_ICONEXCLAMATION);

		QuitSDLOpenGL();
		
		exit(-1);
	}

	testHull.worldCenter.x = half_window_width;
	testHull.worldCenter.y = half_window_height;

	lightSystem.addConvexHull(&testHull);

	// ----------------------------- Load Resources ----------------------------

	TextureDesc floor;
	LoadIMG("floor1.png", floor);

	TextureDesc testImage;
	LoadIMG("testImage.png", testImage);

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

	return EXIT_SUCCESS;
}