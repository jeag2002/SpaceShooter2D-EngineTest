/*
MANAGER.H. ARRANQUE DE TODOS LOS SUBSISTEMAS
*/

#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include "Stdafx.h"

class Manager{

public:
    Manager(LogEngine *_gLogEngine, GlobalEngine *_global){
        gLogEngine = _gLogEngine;
        global = _global;}
    ~Manager(){}
    virtual void startUp(){};
    virtual void shutDown(){};

protected:

    LogEngine *gLogEngine;
    GlobalEngine *global;

};


#endif // MANAGER_H_INCLUDED
