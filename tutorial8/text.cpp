/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "text.h"
#include <string.h>
#include <malloc.h>
#include "TexturedObject.h"

#define MAX_CHARACTERS 67

typedef struct {
  S32BIT x;
  S32BIT y;
} Point;

typedef struct {
  BYTE pt1;
  BYTE pt2;
} Line;

typedef struct {
  BYTE numPts;
  BYTE numLines;
} Character;

//**********
//
// Defines a crude character set out of points and lines.
//
//**********

  Point APts[] = {{0, 6}, {0, 1}, {1, 0}, {3, 0}, {4, 1}, {4, 6}, {4, 3}, {0, 3}};
  Line ALines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {6, 7}};

  Point BPts[] = {{0, 0}, {0, 6}, {3, 6}, {4, 5}, {4, 4}, {3, 3}, {4, 2}, {4, 1}, {3, 0}, {0, 3}};
  Line BLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 9}, {5, 6}, {6, 7}, {7, 8}, {8, 0}};

  Point CPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}};
  Line CLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  Point DPts[] = {{0, 0}, {0, 6}, {3, 6}, {4, 5}, {4, 1}, {3, 0}};
  Line DLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};

  Point EPts[] = {{0, 0}, {0, 6}, {4, 6}, {0, 3}, {3, 3}, {4, 0}};
  Line ELines[] = {{0, 1}, {1, 2}, {3, 4}, {0, 5}};

  Point FPts[] = {{0, 0}, {0, 6}, {0, 3}, {3, 3}, {4, 0}};
  Line FLines[] = {{0, 1}, {2, 3}, {0, 4}};

  Point GPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 3}, {2, 3}};
  Line GLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}};

  Point HPts[] = {{0, 6}, {0, 0}, {0, 3}, {4, 3}, {4, 0}, {4, 6}};
  Line HLines[] = {{0, 1}, {2, 3}, {4, 5}};

  Point IPts[] = {{4, 0}, {0, 0}, {2, 0}, {2, 6}, {0, 6}, {4, 6}};
  Line ILines[] = {{0, 1}, {2, 3}, {4, 5}};

  Point JPts[] = {{4, 0}, {4, 5}, {3, 6}, {1, 6}, {0, 5}, {0, 4}};
  Line JLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  Point KPts[] = {{0, 0}, {0, 6}, {0, 3}, {2, 3}, {4, 0}, {4, 1}, {4, 6}, {4, 5}};
  Line KLines[] = {{0, 1}, {2, 3}, {3, 7}, {3, 5}, {6, 7}, {4, 5}};

  Point LPts[] = {{0, 0}, {0, 6}, {4, 6}};
  Line LLines[] = {{0, 1}, {1, 2}};

  Point MPts[] = {{0, 0}, {0, 6}, {4, 0}, {4, 6}, {2, 3}};
  Line MLines[] = {{0, 1}, {2, 3}, {0, 4}, {2, 4}};

  Point NPts[] = {{0, 0}, {0, 6}, {4, 0}, {4, 6}};
  Line NLines[] = {{0, 1}, {2, 3}, {0, 3}};

  Point OPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}};
  Line OLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 0}};

  Point PPts[] = {{0, 0}, {0, 6}, {3, 0}, {4, 1}, {4, 2}, {3, 3}, {0, 3}};
  Line PLines[] = {{1, 0}, {0, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point QPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {2, 4}, {4, 6}};
  Line QLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 0}, {8, 9}};

  Point RPts[] = {{0, 0}, {0, 6}, {3, 0}, {4, 1}, {4, 2}, {3, 3}, {0, 3}, {4, 6}};
  Line RLines[] = {{1, 0}, {0, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {5, 7}};

  Point SPts[] = {{4,1}, {3,0}, {1,0}, {0,1}, {0,2}, {1,3}, {3,3}, {4,4}, {4,5}, {3,6}, {1,6}, {0,5}};
  Line SLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}};

  Point TPts[] = {{0,0}, {4,0}, {2,0}, {2,6}};
  Line TLines[] = {{0, 1}, {2, 3}};

  Point UPts[] = {{0,0}, {0,5}, {1, 6}, {3, 6}, {4, 5}, {4, 0}};
  Line ULines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  Point VPts[] = {{0,0}, {0,3}, {2,6}, {4, 3}, {4, 0}};
  Line VLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};

  Point WPts[] = {{0,0}, {0,6}, {2,4}, {4, 6}, {4, 0}};
  Line WLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};

  Point XPts[] = {{0,0}, {0,1}, {4,5}, {4, 6}, {4, 0}, {4, 1}, {0, 5}, {0, 6}};
  Line XLines[] = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}};

  Point YPts[] = {{0,0}, {0,2}, {2,3}, {2,6}, {4,0}, {4,2}};
  Line YLines[] = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 2}};

  Point ZPts[] = {{0,0}, {4,0}, {4,1}, {0,5}, {0,6}, {4, 6}};
  Line ZLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  Point aPts[] = {{1,2}, {3,2}, {4,3}, {4,6}, {1,6}, {0, 5}, {1, 4}, {4, 4}};
  Line aLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  Point bPts[] = {{0,0}, {0,6}, {3,6}, {4,5}, {4,4}, {3, 3}, {0, 3}};
  Line bLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point cPts[] = {{4,3}, {1,3}, {0,4}, {0,5}, {1,6}, {4, 6}};
  Line cLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  Point dPts[] = {{4, 0}, {4, 6}, {1, 6}, {0, 5}, {0, 4}, {1, 3}, {4, 3}};
  Line dLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point ePts[] = {{0, 4}, {3, 4}, {4, 3}, {3, 2}, {1, 2}, {0, 3}, {0, 5}, {1, 6}, {4, 6}};
  Line eLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}};

  Point fPts[] = {{4, 1}, {3, 0}, {2, 0}, {1, 1}, {1, 6}, {0, 3}, {3, 3}};
  Line fLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {5, 6}};

  Point gPts[] = {{1, 8}, {3, 8}, {4, 7}, {4, 4}, {3, 3}, {1, 3}, {0, 4}, {0, 5}, {1, 6}, {4, 6}};
  Line gLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}};

  Point hPts[] = {{0, 0}, {0, 6}, {0, 3}, {3, 3}, {4, 4}, {4, 6}};
  Line hLines[] = {{0, 1}, {2, 3}, {3, 4}, {4, 5}};

  Point iPts[] = {{2, 1}, {1, 3}, {2, 3}, {2, 6}, {1, 6}, {3, 6}};
  Line iLines[] = {{0, 0}, {1, 2}, {2, 3}, {4, 5}};

  Point jPts[] = {{3, 2}, {2, 4}, {3, 4}, {3, 7}, {2, 8}, {1, 8}, {0, 7}};
  Line jLines[] = {{0, 0}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point kPts[] = {{0, 0}, {0, 6}, {0, 4}, {1, 4}, {3, 2}, {3, 6}};
  Line kLines[] = {{0, 1}, {2, 3}, {3, 4}, {3, 5}};

  Point lPts[] = {{1, 0}, {2, 0}, {2, 6}, {1, 6}, {3, 6}};
  Line lLines[] = {{0, 1}, {1, 2}, {3, 4}};

  Point mPts[] = {{0, 6}, {0, 4}, {1, 3}, {2, 4}, {3, 3}, {4, 4}, {4, 6}};
  Line mLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point nPts[] = {{0, 6}, {0, 3}, {3, 3}, {4, 4}, {4, 6}};
  Line nLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};

  Point oPts[] = {{0, 4}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 4}, {3, 3}, {1, 3}};
  Line oLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 0}};

  Point pPts[] = {{0, 8}, {0, 4}, {1, 3}, {3, 3}, {4, 4}, {4, 5}, {3, 6}, {0, 6}};
  Line pLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  Point qPts[] = {{4, 8}, {4, 4}, {3, 3}, {1, 3}, {0, 4}, {0, 5}, {1, 6}, {4, 6}};
  Line qLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  Point rPts[] = {{1, 6}, {1, 3}, {3, 3}, {4, 4}};
  Line rLines[] = {{0, 1}, {1, 2}, {2, 3}};

  Point sPts[] = {{4, 2}, {1, 2}, {0, 3}, {1, 4}, {3, 4}, {4, 5}, {3, 6}, {0, 6}};
  Line sLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};

  Point tPts[] = {{0, 2}, {3, 2}, {1, 1}, {1, 5}, {2, 6}, {3, 5}};
  Line tLines[] = {{0, 1}, {2, 3}, {3, 4}, {4, 5}};

  Point uPts[] = {{0, 3}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 3}};
  Line uLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

  Point vPts[] = {{0, 3}, {0, 4}, {2, 6}, {4, 4}, {4, 3}};
  Line vLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};

  Point wPts[] = {{0, 3}, {0, 5}, {1, 6}, {2, 5}, {3, 6}, {4, 5}, {4, 3}};
  Line wLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point xPts[] = {{1, 3}, {4, 6}, {0, 6}, {3, 3}};
  Line xLines[] = {{0, 1}, {2, 3}};

  Point yPts[] = {{0, 3}, {0, 5}, {1, 6}, {3, 6}, {3, 3}, {3, 7}, {2, 8}};
  Line yLines[] = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 6}};

  Point zPts[] = {{0, 3}, {3, 3}, {0, 6}, {3, 6}};
  Line zLines[] = {{0, 1}, {1, 2}, {2, 3}};

  Point zeroPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}};
  Line zeroLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 0}, {0, 4}};

  Point onePts[] = {{1, 1}, {2, 0}, {2, 6}, {1, 6}, {3, 6}};
  Line oneLines[] = {{0, 1}, {1, 2}, {3, 4}};

  Point twoPts[] = {{0, 1}, {1, 0}, {3, 0}, {4, 1}, {4, 2}, {0, 6}, {4, 6}};
  Line twoLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};

  Point threePts[] = {{0, 1}, {1, 0}, {3, 0}, {4, 1}, {4, 2}, {3, 3}, {2, 3}, {4, 4}, {4, 5}, {3, 6}, {1, 6}, {0, 5}};
  Line threeLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {5, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}};

  Point fourPts[] = {{0, 0}, {0, 3}, {4, 3}, {3, 0}, {3, 6}};
  Line fourLines[] = {{0, 1}, {1, 2}, {3, 4}};

  Point fivePts[] = {{4, 0}, {0, 0}, {0, 2}, {3, 2}, {4, 3}, {4, 5}, {3, 6}, {1, 6}, {0, 5}};
  Line fiveLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}};

  Point sixPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 4}, {3, 3}, {0, 3}};
  Line sixLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}};

  Point sevenPts[] = {{0, 0}, {4, 0}, {2, 6}};
  Line sevenLines[] = {{0, 1}, {1, 2}};

  Point eightPts[] = {{4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 3}, {0, 4}, {0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 4}, {3, 3}, {4, 2}};
  Line eightLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 0}, {5, 12}};

  Point ninePts[] = {{0, 5}, {1, 6}, {3, 6}, {4, 5}, {4, 1}, {3, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 3}, {4, 3}};
  Line nineLines[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}};

  Point dotPts[] = {{2, 5}, {2, 6}};
  Line dotLines[] = {{0, 1}};

  Point quotePts[] = {{1, 0}, {1, 1}, {3, 0}, {3, 1}};
  Line quoteLines[] = {{0, 1}, {2, 3}};

  Point colonPts[] = {{2, 0}, {2, 1}, {2, 5}, {2, 6}};
  Line colonLines[] = {{0, 1}, {2, 3}};

  Point commaPts[] = {{1, 6}, {0, 7}};
  Line commaLines[] = {{0, 1}};

  Point lParenPts[] = {{2, 0}, {1, 2}, {1, 4}, {2, 6}};
  Line lParenLines[] = {{0, 1}, {1, 2}, {2, 3}};

  Point rParenPts[] = {{2, 0}, {3, 2}, {3, 4}, {2, 6}};
  Line rParenLines[] = {{0, 1}, {1, 2}, {2, 3}};

  // Count of points, lines
  Character chars[] = {{8, 6}, {10, 10}, {8, 7}, {6, 6}, {6, 4}, // E
                  {5, 3}, {10, 9}, {6, 3}, {6, 3}, {6, 5}, // J
                  {8, 6}, {3, 2}, {5, 4}, {4, 3}, {8, 8}, // O
                  {7, 6}, {10, 9}, {8, 7}, {12, 11}, {4, 2}, // T
                  {6, 5}, {5, 4}, {5, 4}, {8, 6}, {6, 5}, // Y
                  {6, 5}, {8, 7}, {7, 6}, {6, 5}, {7, 6}, // d
                  {9, 8}, {7, 5}, {10, 9}, {6, 4}, {6, 4}, // i
                  {7, 6}, {6, 4}, {5, 3}, {7, 6}, {5, 4}, // n
                  {8, 8}, {8, 7}, {8, 7},  {4, 3}, {8, 7}, // s
                  {6, 4}, {6, 5}, {5, 4}, {7, 6}, {4, 2},  // x
                  {7, 5}, {4, 3},
                  {8, 9}, {5, 3}, {7, 6}, {12, 11}, // 3
                  {5, 3}, {9, 8}, {11, 10}, {3, 2}, {14, 15}, // 8
                  {11, 10}, {2, 1}, {4, 2}, {4, 2}, {2, 1},
                  {4, 3}, {4, 3}};

  Line *lines[] = {ALines, BLines, CLines, DLines, ELines, // E
                    FLines, GLines, HLines, ILines, JLines, // J
                    KLines, LLines, MLines, NLines, OLines, // O
                    PLines, QLines, RLines, SLines, TLines, // T
                    ULines, VLines, WLines, XLines, YLines, // Y
                    ZLines, aLines, bLines, cLines, dLines, // d
                    eLines, fLines, gLines, hLines, iLines, // i
                    jLines, kLines, lLines, mLines, nLines, // n
                    oLines, pLines, qLines, rLines, sLines, // s
                    tLines, uLines, vLines, wLines, xLines, // x
                    yLines, zLines,
                    zeroLines, oneLines, twoLines, // 2
                    threeLines, fourLines, fiveLines, sixLines, // 6
                    sevenLines, eightLines, nineLines, dotLines, quoteLines,
                    colonLines, commaLines, lParenLines, rParenLines};
  Point *points[] = {APts, BPts, CPts, DPts, EPts, // e
                    FPts, GPts, HPts, IPts, JPts, // j
                    KPts, LPts, MPts, NPts, OPts, // o
                    PPts, QPts, RPts, SPts, TPts, // t
                    UPts, VPts, WPts, XPts, YPts, // y
                    ZPts, aPts, bPts, cPts, dPts, // d
                    ePts, fPts, gPts, hPts, iPts, // i
                    jPts, kPts, lPts, mPts, nPts, // n
                    oPts, pPts, qPts, rPts, sPts, // s
                    tPts, uPts, vPts, wPts, xPts, // x
                    yPts, zPts,
                    zeroPts, onePts, twoPts, //2
                    threePts, fourPts, fivePts, sixPts, //6
                    sevenPts, eightPts, ninePts, dotPts, quotePts,
                    colonPts, commaPts, lParenPts, rParenPts};

// Tracks each character's VBO
static GLuint charVBO[MAX_CHARACTERS];

// Figures out the max number of points needed for a character, and allocates appropriate buffer
void AllocateTextBuffers() {

  GLfixed *vertexBuff;

  // Create VBOs for each character we support
  for (int i = 0; i < MAX_CHARACTERS; i ++) {
    // Allocate some space for a temporary vertex buffer
    vertexBuff = (GLfixed *)malloc(sizeof(GLfixed) * chars[i].numLines * 4);

    for (int j = 0; j < chars[i].numLines; j++) {
      // Build up the two points that make up this line
      vertexBuff[j * 4 + 0] = points[i][lines[i][j].pt1].x << 16;
      vertexBuff[j * 4 + 1] = -points[i][lines[i][j].pt1].y << 16;
      vertexBuff[j * 4 + 2] = points[i][lines[i][j].pt2].x << 16;
      vertexBuff[j * 4 + 3] = -points[i][lines[i][j].pt2].y << 16;
    }

    // Allocate a VBO for this character
    glGenBuffers(1, &(charVBO[i]));
    glBindBuffer(GL_ARRAY_BUFFER, charVBO[i]);

    // Copy data into buffer
    glBufferData(GL_ARRAY_BUFFER, chars[i].numLines * sizeof(GLfixed) * 4, vertexBuff, GL_STATIC_DRAW);

    // No longer needed
    delete vertexBuff;
  }
}

void FreeTextBuffers() {
  for (int i = 0; i < MAX_CHARACTERS; i++)
    glDeleteBuffers(1, &charVBO[i]);
}

// Draws a single character
void DrawCharacter(char c, U32BIT x, U32BIT y, U32BIT size) {

  unsigned short index = 1000;

  if (c >= '0' && c <= '9')
    index = c - '0' + 52;
  else if (c >= 'A' && c <= 'Z')
    index = c - 'A';
  else if (c >= 'a' && c <= 'z')
    index = c - 'a' + 26;
  else if (c =='.')
    index = 62;
  else if (c =='\"')
    index = 63;
  else if (c ==':')
    index = 64;
  else if (c ==',')
    index = 65;
  else if (c =='(')
    index = 66;
  else if (c ==')')
    index = 67;

  if (index > MAX_CHARACTERS)
    return;

  // Move, rotate, scale, and draw object.
  glPushMatrix();
    glTranslatex(x, y, 0);
    glScalex(size, size, 0);
    // Point to our vertex array
    glBindBuffer(GL_ARRAY_BUFFER, charVBO[index]);
    glVertexPointer(2, GL_FIXED, 0, 0);

    //glDrawArrays(GL_LINES, 0, chars[index].numLines * 2);
  glPopMatrix();
}

// Draws some text in the appropriate location
// Be sure to set your color before calling this

void DrawString(char *text, S32BIT x, S32BIT y, S32BIT size) {
  S32BIT curPos = x;
  S32BIT step = ((6 << 8) * (size >> 8));


  // Make necessary OpenGL changes
  // Anti-aliasing isn't supported in PowerVR hardware.
  glDisable(GL_BLEND);

  glEnableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glLineWidthx(f2x(3));

  while (*text) {
    DrawCharacter(*text, curPos, y, size);

    curPos += step;
    text++;
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

}

// Similar to DrawString, but coordinate is location to center text aroud.
void DrawCenteredString(char *text, S32BIT x, S32BIT y, S32BIT size) {
  S32BIT step = ((6 << 8) * (size >> 8));
  S32BIT height = ((7 << 8) * (size >> 8));

  S32BIT width = step * strlen(text);
  x = x - (width >> 1);
  y -= (height >> 1);

  DrawString(text, x, y, size);
}
