/*
INITENGINE_H CARGAR FICHERO GLOBAL.INI
*/


#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "Stdafx.h"
#include "ConfigFileEngine.h"

class InitEngine{

public:
        InitEngine(){gLogEngine=NULL; global=NULL;}
        InitEngine(LogEngine *_gLogEngine, GlobalEngine *_global);
        ~InitEngine();

private:
        LogEngine *gLogEngine;
        GlobalEngine *global;
        void processConfig(char *path);
};
#endif // INIT_H_INCLUDED

