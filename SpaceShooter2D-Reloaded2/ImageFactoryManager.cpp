#include "ImageFactoryManager.h"


void ImageFactoryManager::startUp(){
    vector<std::string> keys = this->global->getImageKeys();
    for (std::vector<std::string>::iterator it = keys.begin() ; it != keys.end(); ++it){
        std::string key = *it;
        std::string path = this->global->getImagePath(key);
        size_t it_1 = img->loadImage(path.c_str(),false);
        DEBUGLOGPTHREE("ImageFactoryManager::startUp() - loadImage %s, key %s ID[%d]",path.c_str(),key.c_str(),it_1);
        this->global->insertImageRefGLUint(key, it_1);
    }
    INFOLOG("IMAGEFACTORYMANAGER - INITIALIZED!");
}


void ImageFactoryManager::shutDown(){
    INFOLOG("IMAGEFACTORYMANAGER - FINISHED!");
}



