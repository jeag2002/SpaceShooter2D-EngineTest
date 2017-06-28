#include "GLText.h"

#include "GLGraphics.h"

namespace Text{
    void DrawString(float x, float y, float z, void* font, const char* text){
        char *c;
        glBindTexture(GL_TEXTURE_2D, NULL); GLGraphics::boundTexture = NULL;
        glRasterPos3f(x, y, z);
        glColor3b(127,127,127);
        for (c= (char*)text; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }
}
