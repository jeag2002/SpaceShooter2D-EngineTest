/*
STEPS.H Clase esqueleto de un estado del juego (Nivel, Menu)
*/


#ifndef STEPS_H_INCLUDED
#define STEPS_H_INCLUDED

#include "Stdafx.h"

class Steps{

    public:

        Steps(){}

        Steps(RenderManager *_gRenderManager, LogEngine *_gLogEngine, GlobalEngine *_global){

            gRenderManager = _gRenderManager;
            gLogEngine = _gLogEngine;
            global = _global;

        }

        virtual void runProcess(){};

    protected:

        RenderManager *gRenderManager;
        LogEngine *gLogEngine;
        GlobalEngine *global;


};

#endif // STEPS_H_INCLUDED
