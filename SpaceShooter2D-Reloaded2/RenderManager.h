/*
RENDERMANAGER_H => Clase que compila los shaders. (se necesitará al menos tres pases)
*/

#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "Manager.h"

class RenderManager : public Manager{

    public:

        RenderManager():Manager(NULL,NULL){programObject = 0;}
        RenderManager(LogEngine *_gLogEngine, GlobalEngine *_global): Manager(_gLogEngine, _global){programObject = 0;}
        ~RenderManager(){programObject = 0;}

        void startUp(const std::string vertexshader, const std::string fragmentshader);
        void shutDown();

        std::string readShaderFile(const std::string fileName);
        GLuint LoadShader ( GLenum type, const std::string shaderSrc);
        GLuint LoadShaderToString( GLenum type, const char *shaderSrc);

        GLuint getProgramObject(){return programObject;}
        void setProgramObject( GLuint _programObject){programObject = _programObject;}

        GLuint getVertexShaderId(){return vertexShader;}
        GLuint getFragmentShaderId(){return fragmentShader;}


    private:

        GLuint programObject;
        GLuint vertexShader;
        GLuint fragmentShader;
};



#endif // RENDERMANAGER_H_INCLUDED
