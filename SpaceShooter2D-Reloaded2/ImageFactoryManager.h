/*
IMAGEFACTORYMANAGER_H: CARGA LOS RECURSOS GRÁFICOS DE LA APLICACION EN MEMORIA, Y ALMACENA SUS UIDs
*/


#ifndef IMAGEFACTORYMANAGER_H_INCLUDED
#define IMAGEFACTORYMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "Image.h"

class ImageFactoryManager: public Manager{

public:

    ImageFactoryManager():Manager(NULL,NULL){/*creo el objeto IMAGE*/}
    ImageFactoryManager(LogEngine *_gLogEngine, GlobalEngine *_global): Manager(_gLogEngine, _global){img = new Image(_gLogEngine);}

    void startUp();
    void shutDown();

private:
    Image *img;

};


#endif // IMAGEFACTORY_H_INCLUDED
