/*
INITPARAMENGINE_H: Procesa los parámetros de entrada del juego
*/

#include "Stdafx.h"

#ifndef INITPARAMENGINE_H_INCLUDED
#define INITPARAMENGINE_H_INCLUDED

#define HELPTAG "-help"
#define LOGTAG "-log"
#define TYPELEVTAG "-typeLev"
#define LEVEL "-level"


class InitParamEngine{

    public:

        InitParamEngine(int argc, char **argv, LogEngine *_gLogEngine, GlobalEngine *_global);
        ~InitParamEngine();

    private:

        void outParameter();


};


#endif // INITPARAMENGINE_H_INCLUDED
