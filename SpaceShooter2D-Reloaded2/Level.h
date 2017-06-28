#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Stdafx.h"
#include "Steps.h"

#define VERTEX_ARRAY	0
#define TEXCOORD_ARRAY	1
#define TEXINDEX_ARRAY  2

class Level: public Steps{

    public:

        Level():Steps(NULL,NULL,NULL){}
        Level(std::string path, RenderManager *_gRenderManager,LogEngine *_gLogEngine, GlobalEngine *_global):Steps(_gRenderManager,_gLogEngine,_global){
            createMap();
            beginEngine();
            DEBUGLOG("Level - LEVEL creado!");
        }
        ~Level(){
            destroyMap();
            endEngine();
            DEBUGLOG("Level - LEVEL destruido!");
        }
        void updateProcess();
        void runProcess();

    private:

        int sizeX; int sizeY;

        GLint linked;
        GLuint m_ui32Vbo;
        GLuint m_ui32Vbo_1;
        GLuint m_ui32Vbo_2;

        GLuint ebo;
        GLint uniformLocation;

        unsigned int m_ui32VertexStride;
        float map[12][16];

        size_t idImage;
        size_t idPlayer;
        size_t idText;

        int num_vertex_text;

        size_t idImageTex;

        void createMap();
        void beginEngine();
        void destroyMap();
        void endEngine();

        int writeText(const char*text, float x, float y, float size);

};

#endif // LEVEL_H_INCLUDED

//float **map_1_x;
//float **map_1_y;
