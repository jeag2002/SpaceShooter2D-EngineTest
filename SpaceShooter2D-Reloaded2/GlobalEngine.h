
/*
GLOBALENGINE_H VARIABLES GLOBALES DEL PROGRAMA
*/

#include <string>
#include <map>
#include <stack>
#include <vector>
#include <utility>
//#include "Steps.h"

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED


//movimientos con los cursores (tanto en WIN32 como en embebido)
typedef struct{

int right;
int left;
int up;
int down;
int sel;
int shot;
int esc;
int pause;

}globalMovement;

//movimientos con el raton (solo en WIN32)
typedef struct{

int x_mouse;
int y_mouse;

}globalMouseMovement;

//PILA STEPS
//std::vector<Steps *> stepStorage;

//IMG_DATA
typedef std::pair<std::string, size_t> imgData;
typedef std::pair<std::string, std::string> stepData;
typedef std::pair<std::string, imgData> outputData;

typedef std::map<std::string,std::pair<std::string,size_t> > StorageIMG;
typedef std::map<std::string,std::pair<std::string,std::string> > StorageSTEPS;


class GlobalEngine{
    public:

    GlobalEngine();
    ~GlobalEngine();

    int getLog(){return log;}
    void setLog(int _log){log = _log;}

    int getScreenH(){return screen_h;}
    void setScreenH(int _value){screen_h = _value;}

    int getScreenW(){return screen_w;}
    void setScreenW(int _value){screen_w = _value;}

    int getScreenD(){return screen_d;}
    void setScreenD(int _value){screen_d = _value;}

    int getNumImages(){return numImages;}
    void setNumImages(int _numImages){numImages = _numImages;}

    int getNumSteps(){return numSteps;}
    void setNumSteps(int _numSteps){numSteps = _numSteps;}

    std::string getStepAct(){return stepAct;}
    void setStepAct(std::string _stepAct){stepAct = _stepAct;}


    globalMovement getGlobalM(){return globalM;}
    void setGlobalM(int _up,int _down, int _left, int _right, int _sel, int _esc, int _shot, int _pause){
        globalM.up = _up;
        globalM.down = _down;
        globalM.left = _left;
        globalM.right = _right;
        globalM.sel = _sel;
        globalM.shot = _shot;
        globalM.esc = _esc;
        globalM.pause = _pause;
    }

    globalMouseMovement getGlobalMouseM(){return globalMouseM;}
    void setGlobalMouseM(int _x, int _y){
        globalMouseM.x_mouse = _x;
        globalMouseM.y_mouse = _y;
    }

    //almacen de recursos
    void insertImageRef(std::string key, std::string path){
        imgData iData;
        iData.first = path;
        iData.second = size_t(0);
        imgStorage.insert ( std::pair<std::string, imgData >(key,iData) );
        keyImgStorage.push_back(key);
    }

    void insertImageRefGLUint(std::string key, size_t index){

        StorageIMG::iterator it;
        it = imgStorage.find(key);
        if (it!=imgStorage.end()){
            imgData iData = it->second;
            iData.second = index;
            imgStorage.insert ( std::pair<std::string, imgData >(key,iData) );
        }


    }

    std::vector<std::string> getImageKeys(){return keyImgStorage;}

    std::string getImagePath(std::string key){
        StorageIMG::iterator it;
        it = imgStorage.find(key);
        if (it!=imgStorage.end()){
            imgData iData = it->second;
            return iData.first;
        }else{
            return "";
        }
    }

    size_t getImageId(std::string key){

        StorageIMG::iterator it;
        it = imgStorage.find(key);
        if (it!=imgStorage.end()){
            imgData iData = it->second;
            return iData.second;
        }else{
            return size_t(0);
        }


    }

    std::string getTypeStorage(std::string key){
        StorageSTEPS::iterator it;
        it = stepReference.find(key);
        if (it!=stepReference.end()){
            stepData sData = it->second;
            return sData.second;
        }else{
            return "";
        }
    }

    std::string getPathStorage(std::string key){
        StorageSTEPS::iterator it;
        it = stepReference.find(key);
        if (it!=stepReference.end()){
            stepData sData = it->second;
            return sData.first;
        }else{
            return "";
        }
    }




    //almacen de estados del juego
    void insertStepStorage(std::string key, std::string path, std::string type){

        stepData sData;
        sData.first = path;
        sData.second = type;

        stepReference.insert(std::pair<std::string,  stepData  >(key,sData) );
        keyStepStorage.push_back(key);
    }


    std::vector<std::string> getStorageKeys(){return keyStepStorage;}


    private:

    //LOG
    int log;

    //SCREEN
    int screen_h;
    int screen_w;
    int screen_d;

    //MOVEMENTS
    globalMovement globalM;
    globalMouseMovement globalMouseM;

    int numImages;
    int numSteps;
    std::string stepAct;

    //IMAGE STORAGE:
    StorageIMG imgStorage;
    std::vector<std::string> keyImgStorage;

    //STEPS
    StorageSTEPS stepReference;
    std::vector<std::string> keyStepStorage;

};

#endif // GLOBAL_H_INCLUDED
