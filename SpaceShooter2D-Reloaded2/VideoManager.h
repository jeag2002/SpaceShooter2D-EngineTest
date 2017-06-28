/*
VIDEOMANAGER_H: ARRANQUE VENTANA NATIVA + EGL
*/


#ifndef VIDEOMANAGER_H_INCLUDED
#define VIDEOMANAGER_H_INCLUDED

#define COLOR_SPACE EGL_COLORSPACE_sRGB
#define ALPHA_FORMAT EGL_ALPHA_FORMAT_NONPRE
#define SURFACE_TYPE EGL_WINDOW_BIT | EGL_PBUFFER_BIT

#include "Stdafx.h"
#include "NativeEngine.h"


class VideoManager : public Manager{

    public:

       VideoManager():Manager(NULL,NULL){nEngineFactory = new NativeEngineFactory(NULL,NULL);}
       VideoManager(LogEngine *_gLogEngine, GlobalEngine *_global): Manager(_gLogEngine, _global){nEngineFactory = new NativeEngineFactory(_gLogEngine, _global);}

       void startUp();
       void shutDown();
       void swapBuffer();

    private:

        NativeEngineFactory *nEngineFactory;

        HWND hWindow;
        HDC hDC;

        EGLConfig glConfig;
        EGLDisplay glDisplay;
        EGLContext glContext;
        EGLSurface glSurface;


        EGLint majorVersion;
        EGLint minorVersion;
        EGLint cEGLConfigs;
        EGLConfig aEGLConfigs[1];

        inline const char* EGLErrorString();

};

#endif // VIDEOMANAGER_H_INCLUDED
