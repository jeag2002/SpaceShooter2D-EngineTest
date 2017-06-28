/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _DEFINES_H
#define _DEFINES_H

// This file contains #defines that either ease development or are likely to change between platforms.

// Some common types, generically named
// Unsigned 16 bit
#define U16BIT unsigned short
// Unsigned 32 bit
#define U32BIT unsigned long
// Signed 32 bit 
#define S32BIT long
// Unsigned 8 bit
#define BYTE unsigned char

// Converts from a float to a 16.16 fixed point number and vice versa.  
// Be wary of x2f, it will kill performance on devices without floating point hardware.
#define f2x(x) ((int)((x) * 65536))
#define x2f(x) ((float)((x) / 65536.0f))

#ifdef WIN32
// Physical size of the window
  #define WINDOW_WIDTH 640
  #define WINDOW_HEIGHT 480
#else
  #define WINDOW_WIDTH 320
  #define WINDOW_HEIGHT 240
#endif

#endif
