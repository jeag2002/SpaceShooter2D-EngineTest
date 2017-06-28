#include "InitParamEngine.h"

/*

-log 1/2/3/4 (1=Debug,2=Info,3=Warn,4=Error)
-typeLev 0/1 (0=Level,1=Random)
-
*/

InitParamEngine::InitParamEngine(int argc, char **argv, LogEngine *_gLogEngine, GlobalEngine *_global){

    bool logLevel = false;
    bool typeLev = false;
    bool Lev = false;


    _gLogEngine->info("InitParamEngine()::InitParamEngine - args %d ",argc);

    if (argc > 1){

        for (int i =1; i<argc; i++){

            std::string data = std::string(argv[i]);

            if (strcmp(data.c_str(),HELPTAG)){
                outParameter();
                exit(0);

            }else if (strcmp(data.c_str(),LOGTAG)){
                logLevel = true;
            }else if (strcmp(data.c_str(),TYPELEVTAG)){
                typeLev = true;
            }else if (strcmp(data.c_str(),LEVEL)){
                Lev = true;
            }else if (logLevel || typeLev) {

                int value = atoi(data.c_str());
                if (value >= 0 && value <= 4){
                    if (logLevel==true){logLevel=false;}
                    if (typeLev==true){typeLev=false;}

                }else{

                    std::cout << "Parametro no reconocido\n" << std::endl;
                    break;

                }
            }else if (Lev){

                Lev=false;

            }else{

                std::cout << "Parametro no reconocido\n" << std::endl;
                break;

            }
        }
    }

    _gLogEngine->info("INITPARAMENGINE - INITIALIZED!");
}


InitParamEngine::~InitParamEngine(){

}


void InitParamEngine::outParameter(){

    std::cout << "Parametros reconocidos: \n" << std::endl;
    std::cout << "-help              : Muestra esta ayuda \n" << std::endl;
    std::cout << "-log [1/2/3/4]     : Nivel de logs\n" << std::endl;
    std::cout << "-typeLev [0/1]     : Tipo de nivel (0=Random;1=Carpeta) \n" << std::endl;
    std::cout << "-level <nom_level> : Nivel \n" << std::endl;


}
