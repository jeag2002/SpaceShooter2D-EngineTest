#include "topdown.h"

void initVariables() {
	int x, y, i;

	/* Turn on the frame rate limit by default */
	delay = 1;

	/*Set the camera height to the default */
	cameraHeight = CAMERA_HEIGHT;

	/* Set the timer for the first time */
	fpsPrevTime = SDL_GetTicks();

	playerData.position.x = mapWidth / 2;
	playerData.position.y = mapHeight / 2;
	playerData.speed = PLAYER_MOVE_SPEED;
	playerData.carRotateSpeed = 150;
	playerData.speedDecay = 0.1;
	playerData.carMaxSpeed = 0.8;
	playerData.carMaxReverseSpeed = 0.2;
	playerData.carAcceleration = 0.5;
	playerData.rotation = 0.0;
	playerData.radius = 0.02;
	playerData.state = STATE_ONFOOT;

	playerData.carHeight = 0.3;
	playerData.carWidth = 0.15;


	/*
	Initialize pedestrians
	*/
	numPeds = 0;
	srand(time(0));
	for(x=0; x<mapWidth; x++) {
		for(y=0; y<mapHeight; y++) {
			if(mapdata[y * mapWidth + x] < HOUSE_ID_START) {
				/*Spawn PEDESTRIAN_DENSITY peds per street tile*/
				for(i=0; i<PEDESTRIAN_DENSITY; i++) {
					if(numPeds < MAX_PEDESTRIANS) {
						pedData[numPeds].position.x = x;
						pedData[numPeds].position.y = y;
						pedData[numPeds].rotation = 0;
						pedData[numPeds].speed = PED_MOVE_SPEED;

						if(rand()%2 == 0) {
							pedData[numPeds].direction.x = (rand()%2 == 0) ? -1 : 1;
							pedData[numPeds].direction.y = 0;
						}
						else {
							pedData[numPeds].direction.x = 0;
							pedData[numPeds].direction.y = (rand()%2 == 0) ? -1 : 1;
						}

						numPeds++;
					}
				}
			}
		}
	}



	/* Temporary stuff, TODO: Load this from a file */
	houses[0][0] = 80;
	houses[0][1] = 100;
	houses[0][2] = 0;
	houses[0][3] = 0;

	houses[1][0] = 120;
	houses[1][1] = 0;
	houses[1][2] = 0;
	houses[1][3] = 100;

	houses[2][0] = 180;
	houses[2][1] = 100;
	houses[2][2] = 100;
	houses[2][3] = 0;

	houses[3][0] = 200;
	houses[3][1] = 0;
	houses[3][2] = 100;
	houses[3][3] = 0;
}

int main(int argc, char *argv[]) {
	int videoFlags;
	int done = 0;
	SDL_Event event;
	const SDL_VideoInfo *videoInfo;
	float x, y;

	SDL_Init(SDL_INIT_VIDEO);
	videoInfo = SDL_GetVideoInfo();

	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	videoFlags |= SDL_RESIZABLE;

	fullscreenWidth = videoInfo->current_w;
	fullscreenHeight = videoInfo->current_h;

	if(videoInfo->hw_available) {
		videoFlags |= SDL_HWSURFACE;
	}
	else {
		videoFlags |= SDL_SWSURFACE;
	}

	if(videoInfo->blit_hw) {
		videoFlags |= SDL_HWACCEL;
	}

	/* SDL and window manager stuff */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, videoFlags);
	SDL_WM_SetCaption("Topdown", "Topdown");

	/* Load the map */
	mapdata = loadMap("map.txt");

	/* Initialize variables */
	initVariables();

	/* Correctly size the window */
	resizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);


	/* Event loop */
	while(!done) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_VIDEORESIZE:
					surface = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, videoFlags);
					resizeWindow(event.resize.w, event.resize.h);
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							SDL_Quit();
							return 0;
							break;

						case SDLK_F11:
							if(surface->flags & SDL_FULLSCREEN) {
								surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, videoFlags & ~SDL_FULLSCREEN);
								resizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
							}
							else {
								surface = SDL_SetVideoMode(fullscreenWidth, fullscreenHeight, 16, videoFlags | SDL_FULLSCREEN);
								resizeWindow(fullscreenWidth, fullscreenHeight);
							}

							break;

						case SDLK_LEFT:
						case SDLK_a:
							playerRotating = -1;
							break;

						case SDLK_RIGHT:
						case SDLK_d:
							playerRotating = 1;
							break;

						case SDLK_UP:
						case SDLK_w:
							playerMoving = 1;
							break;

						case SDLK_DOWN:
						case SDLK_s:
							playerMoving = -1;
							break;

						case SDLK_t:
							delay = !delay;
							break;

						case SDLK_RETURN:
							if(playerData.state == STATE_ONFOOT) {
								playerData.state = STATE_DRIVING;
								playerData.speed = 0;
							}
							else {
								playerData.state = STATE_ONFOOT;
								playerData.speed = PLAYER_MOVE_SPEED;
							}

							break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button) {
						case SDL_BUTTON_WHEELUP:
							cameraHeight += 0.5;
							break;

						case SDL_BUTTON_WHEELDOWN:
							cameraHeight -= 0.5;
							break;

						case SDL_BUTTON_LEFT:
							mouseDown = 1;
							break;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					switch(event.button.button) {
						case SDL_BUTTON_LEFT:
							mouseDown = 0;
							break;
					}
					break;

				case SDL_MOUSEMOTION:
					/* event.motion.x, event.motion.y */
					if(playerData.state == STATE_ONFOOT) {
						x = (((float)event.motion.x/(float)currentWidth) * 2.0 - 1.0);
						y = (((float)(currentHeight-event.motion.y)/(float)currentHeight) * 2.0 - 1.0);

						if(sqrt(x*x + y*y) > 0.01) { /* prevent black holes */
							if(y >= 0 && x >= 0) {
								playerData.rotation = (180.0 / M_PI) * atan(x / y);
							}
							else if(y < 0 && x >= 0) {
								playerData.rotation = 90 + (180.0 / M_PI) * atan(-y / x);
							}
							else if(y < 0 && x < 0) {
								playerData.rotation = -90 - (180.0 / M_PI) * atan(-y / -x);
							}
							else {
								playerData.rotation = 270 + (180.0 / M_PI) * atan(y / -x);
							}

							while(playerData.rotation < 0.0) playerData.rotation += 360.0;
							while(playerData.rotation > 360.0) playerData.rotation -= 360.0;
						}
					}
					break;

				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
						case SDLK_RIGHT:
						case SDLK_a:
						case SDLK_d:
							playerRotating = 0;
							break;

						case SDLK_UP:
						case SDLK_DOWN:
						case SDLK_w:
						case SDLK_s:
							playerMoving = 0;
							break;
					}
					break;

				case SDL_QUIT:
					done = 1;
					break;

				default:
					break;
			}
		}

		nowTime = SDL_GetTicks();
		dt = (nowTime - prevTime) / 1000.0;
		prevTime = nowTime;

		/* Make the player actually move */
		movePlayer();

		/* Move pedestrians */
		/*movePeds();*/

		/* Calculate FPS */
		fpsNowTime = nowTime;
		if((fpsNowTime - fpsPrevTime) >= 500) {
			dt = (fpsNowTime - fpsPrevTime) / 1000.0;
			fps = (float)frames / dt;

			fpsPrevTime = fpsNowTime;
			frames = 0;
		}

		/* Sleep accordingly */
		frames++;
		if(delay) SDL_Delay(1000.0/FPS_LIMIT - dt);
		drawGLScene();
	}

	SDL_Quit();

	return 0;
}
