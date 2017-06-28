/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "VBOAllocator.h"
#include "defines.h"

typedef struct {
  GLfixed *buffer;
  GLuint vboNo;
} VBO_REC;

#define MAX_VBO 50

// TODO:  Make this nicer!
static VBO_REC VboArray[MAX_VBO];
static int NumVbo = 0;


// Returns a VBO containing the vertices for a rectangle with given width and height
GLuint GetVBO(GLfixed *buffer) {

  for (int i = 0; i < NumVbo; i++) {
    if (VboArray[i].buffer == buffer)
      return VboArray[i].vboNo;
  }

  // Make sure we aren't already full
  if (NumVbo == MAX_VBO)
    return 0;

  VBO_REC *rec = &VboArray[NumVbo];
  // Allocate a new VBO
  glGenBuffers(1, &(rec->vboNo));
  rec->buffer = buffer;

  // Bind to the buffer
  glBindBuffer(GL_ARRAY_BUFFER, rec->vboNo);

  // Copy data into buffer
  glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfixed), buffer, GL_STATIC_DRAW);

  // Specify offsets for both vertex and tex coords
  
//  glVertexPointer(2, GL_FIXED, 4 * sizeof(GLfixed), 0);
//  glTexCoordPointer(2, GL_FIXED, 4 * sizeof(GLfixed), (GLvoid *)(2 * sizeof(GLfixed)));

  NumVbo++;

  return rec->vboNo;

}


