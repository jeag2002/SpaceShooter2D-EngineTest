#include "topdown.h"

int drawGLScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*Draw map*/
	drawMap();

	/*Player*/
	drawPlayer();

	/*Peds*/
	drawPeds();

	/*Debug info*/
	drawInfo();

	SDL_GL_SwapBuffers();

	return(1);
}

/*
void ownPerspective(float fovy, float aspect, float zNear,  float zFar){
  GLdouble xmin, xmax, ymin, ymax, aspectFixed, znearFixed;

  aspectFixed = (GLdouble)aspect;
  znearFixed = (GLdouble)zNear;

  ymax = znearFixed * (double)tanf(fovy * 3.1415962f / 360.0f);
  ymin = -ymax;

  xmin = ymin * aspectFixed;
  xmax = ymax * aspectFixed;
  glFrustum(xmin, xmax, ymin, ymax, znearFixed, (double)zFar);
}
*/


/*
void ownPerspective(GLdouble fovx, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{

   GLdouble xmin, xmax, ymin, ymax;
   GLdouble m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

   xmax = zNear * tan(fovx * M_PI / 360.0);
   xmin = -xmax;

   ymin = xmin / aspect;
   ymax = xmax / aspect;

   m[0,0] = (2.0 * zNear) / (xmax - xmin);
   m[1,1] = (2.0 * zNear) / (ymax - ymin);
   m[2,2] = -(zFar + zNear) / (zFar - zNear);

   m[0,2] = (xmax + xmin) / (xmax - xmin);
   m[1,2] = (ymax + ymin) / (ymax - ymin);
   m[3,2] = -1.0;

   m[2,3] = -(2.0 * zFar * zNear) / (zFar - zNear);

   glMultMatrixd(m);
}
*/


int resizeWindow(int width, int height) {
	GLfloat ratio;

	/*This is here because windows opengl likes to clean up textures after every resize...*/
	initGL();

	if (height == 0) height = 1;

	ratio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	currentWidth = width;
	currentHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ratio, 0.1f, 500.0f);
	/*ownPerspective(45.0f, ratio, 0.1f, 500.0f);*/


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	return 1;
}

int initGL() {
	if(!loadGLTextures()) {
		printf("error!\n");
		return 1;
	}

	glEnable(GL_TEXTURE_2D);
	/*glShadeModel(GL_SMOOTH);*/
	glEnable(GL_LINE_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/*
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	/*blending stuff*/
	/*glColor4f(1.0f, 1.0f, 1.0f, 0.5f);*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	/*glEnable(GL_BLEND);*/

	return 1;
}

void viewOrtho() {
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, currentWidth, currentHeight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void viewPerspective() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
