/*
NATIVEENGINEFACTORY.H INICIALIZA Y ENLAZA EL MOTOR EGL CON VENTANA NATIVA. (WIN32, LINUX, ANDROID?)
*/

#include "Stdafx.h"
#include "NativeWin32Engine.h"

#ifndef NATIVEENGINE_H_INCLUDED
#define NATIVEENGINE_H_INCLUDED

class NativeEngineFactory{

    public:

        NativeEngineFactory(LogEngine *_gLogEngine, GlobalEngine *_global){
            #ifdef NATIVEWIN32
                nW32Engine = new NativeWin32Engine(_gLogEngine, _global);
            #endif
        }

        HWND create_window(int uiWidth, int uiHeight){
            #ifdef NATIVEWIN32
                return nW32Engine->create_window(uiWidth,uiHeight);
            #endif
        }




    private:

        NativeWin32Engine *nW32Engine;

};
#endif // NATIVEENGINE_H_INCLUDED
