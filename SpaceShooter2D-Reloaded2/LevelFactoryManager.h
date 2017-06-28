#ifndef LEVELFACTORYMANAGER_H_INCLUDED
#define LEVELFACTORYMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "RenderManager.h"
#include "ClockEngine.h"
#include "VideoManager.h"
#include "Level.h"

#define LEVEL "LEVEL"

class LevelFactoryManager : Manager{

    public:

        LevelFactoryManager(RenderManager *_gRenderManager,
                            ClockEngine *_gClockEngine,
                            LogEngine *_gLogEngine,
                            GlobalEngine *_global,
                            VideoManager *_gVideoManager):Manager(_gLogEngine, _global){
                                gRenderManager = _gRenderManager;
                                gClockEngine = _gClockEngine;
                                gVideoManager = _gVideoManager;
                            }
        ~LevelFactoryManager(){}
        void startUp();
        void runLevel();
        void shutDown();

    private:

        Level *actLevel;
        std::vector <Level *> LevelStorage;
        RenderManager *gRenderManager;
        ClockEngine *gClockEngine;
        VideoManager *gVideoManager;
};


#endif // LEVELFACTORYMANAGER_H_INCLUDED
