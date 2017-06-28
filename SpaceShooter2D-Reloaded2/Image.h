/*
IMAGE_H

Clase que almacena las imágenes en memoria.
1-Estudiar carga imágenes comprimidas.

*/

#include "Stdafx.h"

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

typedef struct image{
    void *data;
    GLenum format;
    GLint width;
    GLint height;
};

class Image {
    public:

        Image (){gLogEngine = NULL;}
        Image( LogEngine *_gLogEngine){gLogEngine = _gLogEngine;};
        ~Image(){gLogEngine = NULL;}

    size_t loadImage(const char* file, bool pure_alpha=false);

    private:

        SDL_Surface *ConvertToRGBA(SDL_Surface *frame);

        LogEngine *gLogEngine;
        size_t _id;
        image img_1;

};

#endif // IMAGE_H_INCLUDED
