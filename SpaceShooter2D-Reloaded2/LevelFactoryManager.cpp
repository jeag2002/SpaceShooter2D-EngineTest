#include "LevelFactoryManager.h"


void LevelFactoryManager::startUp(){

    vector<std::string> keys = this->global->getStorageKeys();
    for (std::vector<std::string>::iterator it = keys.begin() ; it != keys.end(); ++it){
        std::string key = *it;

        std::string data = this->global->getTypeStorage(key);
        std::string path = this->global->getPathStorage(key);

        INFOLOGPTHREE("levelFactoryManager::startUp() processing key %s data %s path %s", key.c_str(), data.c_str(), path.c_str());

         //if (strcmp(data.c_str(), LEVEL)){
        Level *lvl = new Level(path,gRenderManager,gLogEngine,global);
        //if (strcmp(this->global->getStepAct().c_str(),key.c_str())){
        actLevel = lvl;
        //}
        LevelStorage.push_back(lvl);
        //}
    }

    INFOLOGPONE("LevelFactoryManager::startUp() - First-Level %s", this->global->getStepAct().c_str());
    INFOLOG("LEVELFACTORYMANAGER - INITIALIZED!");
}


void LevelFactoryManager::runLevel() {

    INFOLOG("LEVELFACTORYMANAGER - RUN!");

    actLevel->runProcess();
    gVideoManager->swapBuffer();
    SDL_Delay(1000);

}

void LevelFactoryManager::shutDown(){
    INFOLOG("LEVELFACTORYMANAGER - FINISHED!");
}
