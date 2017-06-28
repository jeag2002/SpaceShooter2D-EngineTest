/*
MAIN: Motor Principal del juego
*/

#include "Stdafx.h"
#include "InitParamEngine.h"
#include "InitEngine.h"
#include "VideoManager.h"
#include "ImageFactoryManager.h"
#include "LevelFactoryManager.h"
#include "RenderManager.h"
#include "Image.h"
#include "ClockEngine.h"

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

using namespace std;

class Main{

    private:

    ClockEngine *gClockEngine;
    GlobalEngine *gGlobalEngine;
    LogEngine *gLogEngine;
    InitEngine *gInitEngine;
    InitParamEngine *gInitParamEngine;
    VideoManager *gVideoManager;
    ImageFactoryManager *gImageFactoryManager;
    RenderManager *gRenderManager;
    LevelFactoryManager *gLevelFactoryManager;

    Image *gImage;

    public:

    Main(int argc,char *argv[]);
    ~Main();

    void initSpaceShooter();
    void runSpaceShooter();
    void endSpaceShooter();
};




#endif // MAIN_H_INCLUDED
