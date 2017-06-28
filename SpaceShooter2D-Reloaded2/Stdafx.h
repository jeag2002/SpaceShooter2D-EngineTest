//.h general que carga todas los demas .h de la aplicación. evita ir declarandolo todo una y otra vez
#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

//librerias ventana nativa <WIN32>
#include <windows.h>
#include <process.h>
#include <stddef.h>
#include <tchar.h>

//OPENGL ES 3.0
#include  <GLES3/gl3.h>
#include  <EGL/egl.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//DEVIL
//#include<IL/il.h>

//SDL
#include <SDL.h>
#include <SDL_image.h>
#undef main

#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

//librerias comunes de mi aplicacion
#include "GlobalEngine.h"
#include "LogEngine.h"
#include "RenderManager.h"

//funciones macro comunes
#define DEBUGLOG(X)(gLogEngine->debug(X))
#define DEBUGLOGPONE(X,Y)(gLogEngine->debug(X,Y))
#define DEBUGLOGPTWO(X,Y,Z)(gLogEngine->debug(X,Y,Z))
#define DEBUGLOGPTHREE(X,Y,Z,Q)(gLogEngine->debug(X,Y,Z,Q))

#define INFOLOG(X)(gLogEngine->info(X))
#define INFOLOGPONE(X,Y)(gLogEngine->info(X,Y))
#define INFOLOGPTWO(X,Y,Z)(gLogEngine->info(X,Y,Z))
#define INFOLOGPTHREE(X,Y,Z,Q)(gLogEngine->info(X,Y,Z,Q))

#define ERRORLOG(X)(gLogEngine->error(X))
#define ERRORLOGP(X,Y)(gLogEngine->error(X,Y))

using namespace std;

#endif // STDAFX_H_INCLUDED
