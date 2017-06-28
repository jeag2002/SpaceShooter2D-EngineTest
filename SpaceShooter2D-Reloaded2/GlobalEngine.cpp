#include "GlobalEngine.h"


GlobalEngine::GlobalEngine(){
    //LOGS
    //valores por defecto
    log= 1;

    //SCREEN
    screen_h = 640;
    screen_w = 480;
    screen_d = 16;

    //RESOURCES
    numImages = 0;
    numSteps = 0;
    stepAct = "";

}


GlobalEngine::~GlobalEngine(){
    //LOGS
    log = 0;

    //SCREEN
    screen_h = 0;
    screen_w = 0;
    screen_d = 0;

    //RESOURCES
    numImages = 0;
    numSteps = 0;
    stepAct = "";
}



