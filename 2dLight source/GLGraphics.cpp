#include "GLGraphics.h"

namespace GLGraphics
{
    int winW;
    int winH;
    GLuint boundTexture;
    GLuint textureFramebufferTexture;
    GLuint textureFramebuffer;
    SDL_Surface* screen;
    SDL_Rect screenRect;

    void Init(bool fullScr)
    {
        if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        }
        winW = 1024;
        winH = 768;

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
        SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 ); // *new*

        //Sets up the screen and displays the window
        screen = SDL_SetVideoMode( winW, winH, 32, SDL_OPENGL | (fullScr*SDL_FULLSCREEN)); // *changed*
        screenRect.x = 0;
        screenRect.y = 0;
        screenRect.w = winW;
        screenRect.h = winH;

        SetGLState();
    }

    void Init(int w, int h, bool fullScr)
    {
        if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        }
        winW = w;
        winH = h;

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
        SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 ); // *new*

        //Sets up the screen and displays the window
        screen = SDL_SetVideoMode( winW, winH, 32, SDL_OPENGL | (fullScr*SDL_FULLSCREEN)  ); // *changed*
        screenRect.x = 0;
        screenRect.y = 0;
        screenRect.w = winW;
        screenRect.h = winH;

        SetGLState();
    }

    void AutoInit(){
        if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        }
        const SDL_VideoInfo* info = SDL_GetVideoInfo();
        winW =  info->current_w;
        winH = info->current_h;

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
        SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 ); // *new*

        //Sets up the screen and displays the window
        screen = SDL_SetVideoMode( winW, winH, 32, SDL_OPENGL | SDL_FULLSCREEN ); // *changed*
        screenRect.x = 0;
        screenRect.y = 0;
        screenRect.w = winW;
        screenRect.h = winH;

        SetGLState();
    }

    void SetGLState(){
        glEnable( GL_TEXTURE_2D ); //Enable 2d texturing

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); //Set clear color (rgba)

        glViewport( 0, 0, winW, winH ); //Set the viewport

        glClear( GL_COLOR_BUFFER_BIT ); //Clear back buffer?

        glMatrixMode( GL_PROJECTION ); //Set to projection
        glLoadIdentity();

        glOrtho(0.0f, winW, winH, 0.0f, -1.0f, 1.0f); //Create orthogonal projection matrix

        glMatrixMode( GL_MODELVIEW ); //Set back to model view
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        glGenTextures(1, &textureFramebufferTexture);
        glBindTexture(GL_TEXTURE_2D, textureFramebufferTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, winW, winH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /* Create the offscreen framebuffer and bind this to the texture */
        glGenFramebuffersEXT(1, &textureFramebuffer);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, textureFramebuffer);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureFramebufferTexture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, NULL);

        //glEnable(GL_POINT_SMOOTH);
    }

    GLuint Load(std::string filename)
    {
        GLuint texture;			// This is a handle to our texture object
        SDL_Surface *surface;	// This surface will tell us the details of the image
        GLenum texture_format;
        GLint  nOfColors;

        if ( (surface = IMG_Load(filename.c_str())) ) {

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image's height is not a power of 2\n");
        }

            // get the number of channels in the SDL surface
            nOfColors = surface->format->BytesPerPixel;
            if (nOfColors == 4)     // contains an alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGBA;
                    else
                            texture_format = GL_BGRA;
            } else if (nOfColors == 3)     // no alpha channel
            {
                    if (surface->format->Rmask == 0x000000ff)
                            texture_format = GL_RGB;
                    else
                            texture_format = GL_BGR;
            } else {
                    printf("warning: the image is not truecolor..  this will probably break\n");
                    // this error should not go unhandled
            }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                          texture_format, GL_UNSIGNED_BYTE, surface->pixels );
        }
        else {
        printf("SDL could not load image: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
        }

        // Free the SDL_Surface only if it was successfully created
        if ( surface ) {
        SDL_FreeSurface( surface );
        }
        return texture;
    }

    GLuint Load(SDL_Surface* surface){
        GLuint texture;			// This is a handle to our texture object
        GLenum texture_format;
        GLint  nOfColors;

        if ( surface ) {

            // Check that the image's width is a power of 2
            if ( (surface->w & (surface->w - 1)) != 0 ) printf("warning: image's width is not a power of 2\n");

            // Also check if the height is a power of 2
            if ( (surface->h & (surface->h - 1)) != 0 )printf("warning: image's height is not a power of 2\n");

                // get the number of channels in the SDL surface
                nOfColors = surface->format->BytesPerPixel;
                if (nOfColors == 4)     // contains an alpha channel
                {
                        if (surface->format->Rmask == 0x000000ff)
                                texture_format = GL_RGBA;
                        else
                                texture_format = GL_BGRA;
                } else if (nOfColors == 3)     // no alpha channel
                {
                        if (surface->format->Rmask == 0x000000ff)
                                texture_format = GL_RGB;
                        else
                                texture_format = GL_BGR;
                } else {
                        printf("warning: the image is not truecolor..  this will probably break\n");
                        // this error should not go unhandled
                }

            // Have OpenGL generate a texture object handle for us
            glGenTextures( 1, &texture );

            // Bind the texture object
            glBindTexture( GL_TEXTURE_2D, texture );

            // Set the texture's stretching properties
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            // Edit the texture object's image data using the information SDL_Surface gives us
            glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                              texture_format, GL_UNSIGNED_BYTE, surface->pixels );
        }
        else {
            printf("SDL could not load image: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        return texture;
    }

    void DrawRect(float x, float y, float w, float h, int r, int g, int b){
        if(boundTexture != NULL){glBindTexture( GL_TEXTURE_2D, NULL ); boundTexture = NULL; }

        glBegin(GL_QUADS);
            glColor3b(r,g,b);
            //Bottom-left vertex (corner)
            glVertex3f( x-w/2, y-h/2, 0.0f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glVertex3f( x+w/2, y-h/2, 0.f );

            //Top-right vertex (corner)
            glVertex3f( x+w/2, y+h/2, 0.f );

            //Top-left vertex (corner)
            glVertex3f( x-w/2, y+h/2, 0.f );

        glEnd();
    }

    void DrawLine(float x1, float y1, float x2, float y2, int r, int g, int b){
        if(boundTexture != NULL){glBindTexture( GL_TEXTURE_2D, NULL ); boundTexture = NULL; }

        glBegin(GL_LINES);
            glColor3b(r,g,b);
            glVertex2f( x1, y1);
            glVertex2f( x2, y2);
        glEnd();
    }

    void DrawPoint(float x, float y, int r, int g, int b){
        if(boundTexture != NULL){glBindTexture( GL_TEXTURE_2D, NULL ); boundTexture = NULL; }

        glBegin(GL_POINTS);
            glColor3b(r,g,b);
            glVertex2f( x, y);
        glEnd();
    }

    void DrawCircle(float x, float y, float R, int n, int r, int g, int b){
        if(boundTexture != NULL){glBindTexture( GL_TEXTURE_2D, NULL ); boundTexture = NULL; }

        glBegin(GL_POLYGON);
            glColor3b(r,g,b);
        for(float i = 0; i < 2*PI; i+= (2*PI)/n){
            glVertex2f(x+cosf(i)*R, y+sinf(i)*R);
        }
        glEnd();
    }

    void DrawImage(GLuint image, float x, float y, float w, float h)
    {
        // Bind the texture to which subsequent calls refer to
        if(boundTexture != image){glBindTexture( GL_TEXTURE_2D, image ); boundTexture = image; }

        //glRotated(rand()%360, 0, 0, 1);

        glBegin( GL_QUADS );
            glColor3b(127,127,127);
            //Bottom-left vertex (corner)

            glTexCoord2i( 0, 0 ); //Position on texture to begin interpolation
            glVertex3f( x, y, 0.0f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glTexCoord2i( 1, 0 );
            glVertex3f( x+w, y, 0.f );

            //Top-right vertex (corner)
            glTexCoord2i( 1, 1 );
            glVertex3f( x+w, y+h, 0.f );

            //Top-left vertex (corner)
            glTexCoord2i( 0, 1 );
            glVertex3f( x, y+h, 0.f );
        glEnd();

    }

    void DrawImage(GLuint image, float x, float y, float w, float h, float r, float g, float b) //127 is max for rgb. WTF.
    {
        // Bind the texture to which subsequent calls refer to
        if(boundTexture != image){glBindTexture( GL_TEXTURE_2D, image ); boundTexture = image; }

        glBegin( GL_QUADS );
            //Bottom-left vertex (corner)
            glColor3b(r, g, b);
            glTexCoord2i( 0, 0 ); //Position on texture to begin interpolation
            glVertex3f( x, y, 0.0f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glTexCoord2i( 1, 0 );
            glVertex3f( x+w, y, 0.f );

            //Top-right vertex (corner)
            glTexCoord2i( 1, 1 );
            glVertex3f( x+w, y+h, 0.f );

            //Top-left vertex (corner)
            glTexCoord2i( 0, 1 );
            glVertex3f( x, y+h, 0.f );
        glEnd();

    }

    void UnbindTex(){
        if(boundTexture != NULL){glBindTexture(GL_TEXTURE_2D, NULL); boundTexture = NULL;}
    }

    void RendertoTexture(){
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, textureFramebuffer);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureFramebufferTexture, 0);
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void RendertoBackBuffer(){
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, NULL);
    }

    void Flip(){
        SDL_GL_SwapBuffers();
        glClear( GL_COLOR_BUFFER_BIT );
    }

    void Quit()
    {
        SDL_FreeSurface(screen);
        SDL_Quit();
    }
}
