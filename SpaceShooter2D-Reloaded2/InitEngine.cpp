#include "InitEngine.h"


InitEngine::InitEngine(LogEngine *_gLogEngine, GlobalEngine *_global){
    gLogEngine = _gLogEngine;
    global = _global;
    processConfig("./data/global.ini");
}

//cargar los datos del fichero
void InitEngine::processConfig(char *path){

    char buff[100];

    ConfigFileEngine config(path);

    this->global->setLog(config.read<int>("log"));
    this->global->setScreenW(config.read<int>("screen_w"));
    this->global->setScreenH(config.read<int>("screen_h"));
    this->global->setScreenD(config.read<int>("screen_d"));

    this->global->setNumSteps(config.read<int>("num_steps"));
    this->global->setNumImages(config.read<int>("num_images"));

    //insertar referencias de las imagenes en el repositorio global

    int value = this->global->getNumImages();
    for (int i=1; i<=value; i++){

        sprintf(buff, "image_%d", i);
        std::string path_to_image = buff;
        path_to_image = config.read<std::string>(path_to_image);
        sprintf(buff, "image_%d_ticked",i);
        std::string path_to_imageKey = buff;
        path_to_imageKey = config.read<std::string>(path_to_imageKey);
        DEBUGLOGPONE("InitEngine - image type %s ", path_to_imageKey.c_str());
        this->global->insertImageRef(path_to_imageKey,path_to_image);
    }

    //insertar referencia de los niveles del motor.

    value = this->global->getNumSteps();
    for (int i=1; i<=value; i++){

        sprintf(buff, "step_%d", i);
        std::string step_key = buff;
        std::string path_to_step = config.read<std::string>(step_key);

        sprintf(buff, "step_%d_type", i);
        std::string step_type = buff;
        step_type = config.read<std::string>(step_type);

        this->global->insertStepStorage(step_key,path_to_step,step_type);
    }

    this->global->setStepAct(config.read<std::string>("step_act"));
}


InitEngine::~InitEngine(){
}
