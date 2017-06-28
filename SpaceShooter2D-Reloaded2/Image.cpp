#include "Image.h"

//cargando imágen.
/*
size_t Image::loadImage(const char* file, bool pure_alpha){

  _id = size_t(0);

   ILuint handle, w, h;

   ilInit();

   ilGenImages(1, &handle);
   ilBindImage(handle);

   ILboolean loaded = ilLoadImage(file);

   if (loaded == IL_FALSE){
        ERRORLOGP("Image - Error al cargar el fichero %s",file);
   }else{

      loaded = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
      if (loaded != IL_FALSE){

          w = ilGetInteger(IL_IMAGE_WIDTH);
          h = ilGetInteger(IL_IMAGE_HEIGHT);

          glGenTextures(1, &_id);
          glBindTexture(GL_TEXTURE_2D, _id);

          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

          // Upload the pixel data.
          glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
          ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
          ilGetData());
      }
  }

  ilDeleteImages(1, &handle);

  return _id;
}*/


size_t Image::loadImage(const char* file, bool pure_alpha){

    _id = size_t(0);

    //En este caso se trata de cargar un BMP
    SDL_Surface *surface = IMG_Load(file);
    //SDL_Surface *surface = SDL_LoadBMP(file);

    if (!surface){
        ERRORLOGP("Image::loadImage Error al cargar la textura %s", IMG_GetError());
        exit(1);
    }

    //surface = ConvertToRGBA(surface);
    /*
    switch (surface->format->BytesPerPixel) {
        case 4:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
                img_1.format = 0x80E1; //GL_BGRA
            }else{
                img_1.format = GL_RGBA;
            }
        break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
                img_1.format = 0x80E0; //GL_BGR
            }else{
                img_1.format = GL_RGB;
            }
        break;
    }*/

    img_1.width = surface->w;
    img_1.height = surface->h;
    img_1.data = surface->pixels;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, img_1.width, img_1.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_1.data);

    //glTexImage2D(GL_TEXTURE_2D, 0, img_1.format, img_1.width, img_1.height, 0, img_1.format, GL_UNSIGNED_BYTE, img_1.data);
    //glTexImage2D(GL_TEXTURE_2D, 0, img_1.format, img_1.width, img_1.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_1.data);

     SDL_FreeSurface(surface);

    return _id;
}


SDL_Surface *Image::ConvertToRGBA(SDL_Surface *frame){

    GLuint it;
    GLuint jt;

            for (jt=0; jt<frame->h; jt++)
            {
                for (it=0; it<frame->w; it++)
                {GLuint *id;
                    switch (frame->format->BytesPerPixel)
                    {
                        case 3:
                             {
                                 unsigned char rvalue;
                                 unsigned char bvalue;

                                 rvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 bvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2);
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=bvalue;
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2)=rvalue;
                             }
                             break;
                        case 4:
                             {
                                 unsigned long rgbvalue;

                                 rgbvalue=*(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 rgbvalue=(rgbvalue & 0xFF00FF00) | ((rgbvalue<<16) & 0x00FF0000) |
                                          ((rgbvalue>>16) & 0x000000FF);
                                 *(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=rgbvalue;
                             }
                             break;
                    }
                }
            }

        switch (frame->format->BytesPerPixel)
        {
            case 3:
                 {
                     GLuint it;
                     GLuint jt;
                     unsigned char rvalue;
                     unsigned char gvalue;
                     unsigned char bvalue;

                     for (jt=0; jt<frame->h/2; jt++)
                     {
                         for (it=0; it<frame->w; it++)
                         {
                             rvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel);
                             gvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1);
                             bvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel)=rvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1)=gvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2)=bvalue;

                         }
                     }
                 }
                 break;

    }

    return frame;
}

