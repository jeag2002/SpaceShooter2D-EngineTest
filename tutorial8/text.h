/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _TEXT_H
#define _TEXT_H

#include "defines.h"

// A really crude text renderer.
// You must call AllocateTextBuffers before using the string drawing funcs

void DrawString(char *text, S32BIT x, S32BIT y, S32BIT size);
void DrawCenteredString(char *text, S32BIT x, S32BIT y, S32BIT size);

void AllocateTextBuffers();
void FreeTextBuffers();

#endif
