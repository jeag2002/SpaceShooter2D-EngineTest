#include "VideoManager.h"

/*Inicializacion EGL*/
void VideoManager::startUp(){


    EGLint surface_attrib_list[] =
    {
          EGL_COLORSPACE,      COLOR_SPACE,
          EGL_ALPHA_FORMAT,   ALPHA_FORMAT,
          EGL_NONE
    };

    EGLint config_attrib_list[] = {
            EGL_LEVEL,				0,
            EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
            EGL_NATIVE_RENDERABLE,	EGL_FALSE,
            EGL_DEPTH_SIZE,			EGL_DONT_CARE,
            EGL_NONE
    };


    EGLint context_attrib_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };


    hWindow = nEngineFactory->create_window(global->getScreenW(),global->getScreenH());
    INFOLOGPTWO("VideoManager - Ventana nativa creada <%d,%d> ",global->getScreenW(),global->getScreenH());

    hDC = GetWindowDC(hWindow);
    glDisplay = eglGetDisplay(hDC);

    if(glDisplay == EGL_NO_DISPLAY){
         glDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
    }

    //EGLint iMajorVersion, iMinorVersion;

    if (!eglInitialize(glDisplay, NULL, NULL)){
        ERRORLOG("Error al inicializar Display EGL");
        exit(-1);
    }

    if (!eglChooseConfig(glDisplay, config_attrib_list, aEGLConfigs, 1, &cEGLConfigs)){
        ERRORLOG("Error al inicializar configuracion EGL");
        exit(-1);
    }

    if (cEGLConfigs != 1){
        ERRORLOGP("Error en la configuracion EGL. %s",EGLErrorString());
        exit(-1);
    }

    glSurface = eglCreateWindowSurface(glDisplay, aEGLConfigs[0], (EGLNativeWindowType)hWindow, NULL);
    if (glSurface == EGL_NO_SURFACE) {
        ERRORLOGP("Error al incializar Superficie EGL. %s",EGLErrorString());
        exit(-1);
        glSurface = eglCreateWindowSurface(glDisplay, aEGLConfigs[0], (EGLNativeWindowType)hWindow, NULL);
        if (glSurface == EGL_NO_SURFACE){
            ERRORLOGP("Error al incializar Superficie EGL. %s", EGLErrorString());
            exit(-1);
        }
    }
    eglBindAPI(EGL_OPENGL_ES_API);

    glContext = eglCreateContext(glDisplay, aEGLConfigs[0], EGL_NO_CONTEXT, context_attrib_list);

    if (glContext  == EGL_NO_CONTEXT) {
        ERRORLOG("Error al crear contexto EGL");
        exit(-1);
    }

    if (!eglMakeCurrent(glDisplay, glSurface, glSurface, glContext)){
        ERRORLOGP("Error al hacer Make Current: %s",EGLErrorString());
        exit(-1);
    }

    char *vendor = (char *)glGetString(GL_VENDOR);
    if (vendor != NULL){DEBUGLOGPONE("VideoManager::startUp --> OPENGL ES 3.0 VENDOR [%s]",vendor);}

    char* version = (char *)glGetString(GL_VERSION);
    if (version != NULL){DEBUGLOGPONE("VideoManager::startUp --> OPENGL ES 3.0 VERSION [%s]",version);}

    char* renderer = (char *)glGetString(GL_RENDERER);
    if (renderer != NULL){DEBUGLOGPONE("VideoManager::startUp--> OPENGL ES 3.0 RENDER VERSION [%s]",renderer);}

    char* extensionList = (char *)glGetString(GL_EXTENSIONS);
    if (extensionList != NULL){
        char *data = "";
        data = strtok(extensionList, " ");

        while(data != NULL){
            DEBUGLOGPONE("VideoManager::startUp --> OPENGL ES 3.0 SUPPORTED EXTENSION [%s]", data);
            data = strtok(NULL, " ");
        }
    }


    INFOLOG("VIDEOMANAGER - INITIALIZED!");
}


inline const char* VideoManager::EGLErrorString(){
	EGLint nErr = eglGetError();
	switch(nErr){
		case EGL_SUCCESS: 				return "EGL_SUCCESS";
		case EGL_BAD_DISPLAY:			return "EGL_BAD_DISPLAY";
		case EGL_NOT_INITIALIZED:		return "EGL_NOT_INITIALIZED";
		case EGL_BAD_ACCESS:			return "EGL_BAD_ACCESS";
		case EGL_BAD_ALLOC:				return "EGL_BAD_ALLOC";
		case EGL_BAD_ATTRIBUTE:			return "EGL_BAD_ATTRIBUTE";
		case EGL_BAD_CONFIG:			return "EGL_BAD_CONFIG";
		case EGL_BAD_CONTEXT:			return "EGL_BAD_CONTEXT";
		case EGL_BAD_CURRENT_SURFACE:	return "EGL_BAD_CURRENT_SURFACE";
		case EGL_BAD_MATCH:				return "EGL_BAD_MATCH";
		case EGL_BAD_NATIVE_PIXMAP:		return "EGL_BAD_NATIVE_PIXMAP";
		case EGL_BAD_NATIVE_WINDOW:		return "EGL_BAD_NATIVE_WINDOW";
		case EGL_BAD_PARAMETER:			return "EGL_BAD_PARAMETER";
		case EGL_BAD_SURFACE:			return "EGL_BAD_SURFACE";
		default:						return "unknown";
	}
}

/*Finalizacion EGL*/
void VideoManager::shutDown(){
    eglMakeCurrent(glDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(glDisplay, glSurface);
    eglDestroyContext(glDisplay, glContext);
    eglTerminate(glDisplay);
    INFOLOG("VIDEOMANAGER - FINISHED!");
}

/*Actualizacion EGL*/
void VideoManager::swapBuffer(){
    eglSwapBuffers(glDisplay, glSurface);
}

