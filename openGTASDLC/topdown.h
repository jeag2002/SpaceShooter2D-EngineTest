#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

/*The windows opengl specification doesn't define this, why?*/
#define GL_BGR			0x80E0

#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define SCREEN_BPP		16

#define PLAYER_ROTATE_SPEED	200.0
#define PLAYER_MOVE_SPEED	0.5

#define PEDESTRIAN_DENSITY	2
#define MAX_PEDESTRIANS		100
#define PED_MOVE_SPEED		0.4

#define CAMERA_HEIGHT		-5

#define NUM_ROAD_TYPES		11
#define NUM_HOUSE_TYPES		4

#define ROAD_ID_START		0
#define HOUSE_ID_START		128

#define STATE_ONFOOT		0
#define STATE_DRIVING		1

#define FPS_LIMIT		60
#define M_PI		3.14159265358979323846

typedef struct vector2_s {
	float x;
	float y;
} vector2;

typedef struct player_s {
	vector2 position;
	float speed;
	float rotation;
	float radius;
	float carHeight;
	float carWidth;
	float carAcceleration;
	float carMaxSpeed;
	float carMaxReverseSpeed; /*this should be a positive value*/
	float carRotateSpeed;
	float speedDecay;
	int state; /*0 = walking, 1 = in car? (TODO)*/
} player;

typedef struct pedestrian_s {
	vector2 position;
	float speed;
	float rotation;
	vector2 direction;
} pedestrian;


/* This actually stores the data*/
player playerData;
pedestrian pedData[MAX_PEDESTRIANS];
unsigned int numPeds;

SDL_Surface *surface;
SDL_Surface *textureImage[NUM_ROAD_TYPES];
SDL_Surface *textureImageFont, *textureImageBuilding;
int fullscreenWidth, fullscreenHeight, currentWidth, currentHeight;
int mouseDown, texturesLoaded, delay;
int playerMoving, playerRotating;
float cameraHeight;
unsigned int prevTime, nowTime, fpsPrevTime, fpsNowTime, frames;
GLuint texture[256];
GLuint fontTexture;
GLuint buildingTexture;
/*float playerData.position.x, playerData.position.y, playerData.rotation;*/
float dt, fps;
unsigned char houses[NUM_HOUSE_TYPES][4];
unsigned char mapWidth, mapHeight;
unsigned char *mapdata;

/*main.c*/
void initVariables();

/*load.c*/
unsigned char *loadMap(char *path);
int loadGLTextures();

/*draw_backend.c*/
/*void ownPerspective(float fovy, float aspect, float zNear,  float zFar);*/
void ownPerspective(GLdouble fovx, GLdouble aspect, GLdouble zNear, GLdouble zFar);
int drawGLScene();
int resizeWindow(int width, int height);
int initGL();
void viewOrtho();
void viewPerspective();

/*draw.c*/
void drawMap();
void drawPlayer();
void drawPeds();
void drawInfo();
void drawString(char *string);
void drawBuilding();
void drawCube();

/*gameplay.c*/
void movePeds();
void movePlayer();

/*collision.c*/
int collideCircle(vector2 center, float radius, vector2 point1, vector2 point2);
int collideRectangle(vector2 corner1, vector2 corner2, vector2 corner3, vector2 corner4, vector2 point1, vector2 point2);
int intersectLines(vector2 point1, vector2 point2, vector2 point3, vector2 point4);


