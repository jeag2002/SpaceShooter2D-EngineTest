/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _VBOALLOCATOR_H
#define _VBOALLOCATOR_H

#include <gles/gl.h>

// Handles storing of vertex & texture buffer information in VBOs.  If the passed in buffer isn't already converted to a VBO, we create one and return
// the resultant VBO.  If one already exists for a given buffer, return it.
GLuint GetVBO(GLfixed *buffer);

#endif
