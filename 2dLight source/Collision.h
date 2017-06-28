#ifndef COLLISION_H
    #define COLLISION_H

#include "vector2.h"
#include "Debug.h"
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#define MAX(a,b) a > b? a : b
#define MIN(a,b) a < b? a : b

//Structure of an arbitrary rectangle,(non axis-aligned)
//Vectors are assumed to be in world space
//TODO add overloaded operators
struct CollisionRect{
    vector2 UL;
    vector2 UR;
    vector2 LR;
    vector2 LL;
};


namespace Collide
{
    // SDL_Surface* on SDL_Surface* collision
    bool isColliding(SDL_Surface*, int, int, SDL_Surface*, int, int);
    // SDL_Surface* on SDL_Surface* bounding box collision
    bool boundCollide(SDL_Surface*, int, int, SDL_Surface*, int, int);
    // Point on SDL_Surface* collision
    bool isColliding(int, int, SDL_Surface*, int, int);
    // Point on SDL_Rect* collision
    bool isColliding(int, int , SDL_Rect*);
    // SDL_Rect* on SDL_Surface* collision
    bool isColliding(SDL_Rect*, SDL_Surface*, int, int);
    // SDL_Rect* on SDL_Rect* collision
    bool isColliding(SDL_Rect*, SDL_Rect*);
    // Line on SDL_Rect* collision
    bool isColliding(vector2, vector2, SDL_Rect*); //x/y is at CENTER of rect.
    //CollideRect on CollideRect Collision
    bool isColliding(CollisionRect, float, CollisionRect, float);
    void rotateRect(CollisionRect*, float);
    void rotatePoint(vector2*, float);
    float scalarProj(vector2, vector2);
    // Checks alpha transparency at a point
    bool isTransparent(SDL_Surface*, int, int);
    // Checks for circle collision
    int CircleCollide(int, int, int, int, int, int);

}

#endif //COLLISION_H

