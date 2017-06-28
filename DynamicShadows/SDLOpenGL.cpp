#include "SDLOpenGL.h"

#include <iostream>
#include <cmath>



unsigned int window_width = 640;
unsigned int window_height = 480;
unsigned int window_bpp = 32;
Uint32 screen_flags = NULL;
bool inOrtho = false;

void ViewOrtho(float zNear, float zFar)
{
	if(!inOrtho)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, window_width, 0, window_height, zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		inOrtho = true;
	}
}

void ViewPerspective(float zNear, float zFar)
{
	if(inOrtho)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective1(45.0, (window_width/window_height), zNear, zFar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		inOrtho = false;
	}
}



void gluPerspective1(float fovy, double aspect, float zNear, float zFar){
	const double pi180 = 0.017453292519943295769236907684886;
	double top, bottom, left, right;
	top = zNear * tan(pi180*fovy/2);
	bottom = -top;
	right = aspect*top;
	left = -right;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustumx(left, right, bottom, top, zNear, zFar);
	glFrustum(left, right, bottom, top, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}



void ResizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
		height=1;										// Making Height Equal One

	glViewport(0, 0, width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective1(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


SDL_Surface *ConvertToRGBA(SDL_Surface *frame){

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






bool LoadIMG(const char* filename, TextureDesc &textureInfo)
{
	
    
    SDL_Surface *frame = NULL;	
	GLuint texture;

    try{
		
		glGenTextures(1, &texture);
		frame = SDL_LoadBMP(filename);

		if (!frame){

			printf("No se puede cargar la imagen %s : %s",filename,IMG_GetError());
			throw "no se ha podido cargar la imagen correctamente";

		}else{
            
			//frame = ConvertToRGBA(frame);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame->w, frame->h, 0, GL_RGB, GL_UNSIGNED_BYTE, frame->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glBindTexture(GL_TEXTURE_2D,texture);
			printf("imagen %s cargada correctamente! uid %d",filename, texture);
		}
    }catch (char *str_error){
        printf("OpenGL error flag %d desc %s", glGetError(),str_error);
        return -1;
    }

    

	GLenum glError = glGetError(); 
			
	if(glError)
		return false;

	textureInfo.width = frame->w;
	textureInfo.height = frame->h;
	textureInfo.hTexture = texture;

	delete frame;

	return true;




	/*
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename,0);

	if(format == FIF_UNKNOWN) // Didn't work, now try to get type from file name
		format = FreeImage_GetFIFFromFilename(filename);

	if(format == FIF_UNKNOWN) // Didn't work again, break
		return false;

	// Automatically detects the format (from over 20 formats!) 
	FIBITMAP* image = FreeImage_Load(format, filename); 

	if(image == NULL) // Didn't work, break
		return false;

	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);
	int w = FreeImage_GetWidth(image); 
	int h = FreeImage_GetHeight(image); 
			
	// Some debugging code 
	char* pixeles = (char*)FreeImage_GetBits(image);
	// FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR). 
	// Now generate the OpenGL texture object 
	GLuint texture;
	glGenTextures(1, &texture); 
			
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (GLvoid*)pixeles ); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	glBindTexture(GL_TEXTURE_2D, texture);*/
}

bool InitSDLOpenGL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  4); // Anti-ailiasing

	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1); // Vsync, might only work in fullscreen mode

	// Create screen and get SDL surface
	if(SDL_SetVideoMode(window_width, window_height, window_bpp, SDL_OPENGL|screen_flags) == NULL)
		return false;

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	ViewPerspective(0.1f, 100.0f);

	ResizeGLScene(window_width, window_height);

	glEnable(GL_CULL_FACE); // Enable backface culling
	glEnable(GL_BLEND); // Enable alpha blending
	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping
	//glEnable(GL_NORMALIZE); // Normalizes normals when scaling to lighting isn't messed up

	// Default blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ------------------------------- Check for Initialization Errors -------------------------------

	if(glGetError() != GL_NO_ERROR)
		return false;

	return true;
}

void QuitSDLOpenGL()
{
	SDL_Quit();
}

void Draw2DQuad(const TextureDesc &textureInfo, float tiles)
{
	float halfWidth = textureInfo.width/2.0f;
	float halfHeight = textureInfo.height/2.0f;

	glBindTexture(GL_TEXTURE_2D, textureInfo.hTexture);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, 0.0f);
		glTexCoord2f(tiles, 0.0f); glVertex3f(halfWidth, -halfHeight, 0.0f);
		glTexCoord2f(tiles, tiles); glVertex3f(halfWidth, halfHeight, 0.0f);
		glTexCoord2f(0.0f, tiles); glVertex3f(-halfWidth, halfHeight, 0.0f);
	glEnd();
}