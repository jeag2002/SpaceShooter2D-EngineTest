/**************************************************************/
/***** FAN GAME SINISTAR REDUX GL Version for EMBEDDED ARCH ***/
/**************************************************************/

/*
(GPL)
Version retomada del SpaceShooter2D-2
Versión final:
1)OpenGL ES 3.0
2)GLFW
*/

#include "Main.h"

Main::Main(int argc,char *argv[]){

    //ClockEngine (marca el ritmo de los framesxsegundos de la aplicacion)
    gClockEngine = new ClockEngine();

    //MemoryEngine (<- de momento, uso el STL)

    //LogEngine
    gLogEngine = new LogEngine();

    //GlobalEngine
    gGlobalEngine = new GlobalEngine();

    //initEngine
    gInitEngine = new InitEngine(gLogEngine, gGlobalEngine);

    //initParamEngine
    gInitParamEngine = new InitParamEngine(argc, argv, gLogEngine, gGlobalEngine);

    //VideoManager
    gVideoManager = new VideoManager(gLogEngine, gGlobalEngine);

    //ImageFactoryManager (se cargan las imagenes. pool de imagenes)
    gImageFactoryManager = new ImageFactoryManager(gLogEngine, gGlobalEngine);

    //RenderManager (renderizado de un nivel)
    gRenderManager = new RenderManager(gLogEngine, gGlobalEngine);

    //LevelFactoryManager (se cargan los datos de los niveles en memoria)
    gLevelFactoryManager = new LevelFactoryManager(gRenderManager, gClockEngine, gLogEngine, gGlobalEngine, gVideoManager);

}

Main::~Main(){
    delete gLevelFactoryManager;
    delete gRenderManager;
    delete gImageFactoryManager;
    delete gVideoManager;
    delete gInitParamEngine;
    delete gInitEngine;
    delete gGlobalEngine;
    delete gLogEngine;
    delete gClockEngine;
}

//INICIALIZAR LOS DIFERENTES SUBSISTEMAS
void Main::initSpaceShooter(){
    gLogEngine->startUp(gGlobalEngine->getLog());
    gVideoManager->startUp();
    gImageFactoryManager->startUp();
    gRenderManager->startUp("./data/shader/initvertex.txt", "./data/shader/initfragment.txt");
    gLevelFactoryManager->startUp();

    INFOLOG("############################################");
    INFOLOG("SINISTAR 1.00.000.1  BEGIN                  ");
    INFOLOG("############################################");
}

void Main::runSpaceShooter(){
    gLevelFactoryManager->runLevel();
}

//FINALIZAR LOS DIFERENTES SUBSISTEMAS
void Main::endSpaceShooter(){
    INFOLOG("############################################");
    INFOLOG("SINISTAR 1.00.000.1  END                    ");
    INFOLOG("############################################");

    gLevelFactoryManager->shutDown();
    gRenderManager->shutDown();
    gImageFactoryManager->shutDown();
    gVideoManager->shutDown();
    gLogEngine->shutDown();
}

void sinistarEnvirontment(int argc,char *argv[]){

    Main *sinistar = new Main(argc,argv);
    sinistar->initSpaceShooter();
    sinistar->runSpaceShooter();
    sinistar->endSpaceShooter();
    delete sinistar;
}

int main (int argc,char *argv[])
{
    sinistarEnvirontment(argc, argv);
    return 0;

}
