#include "Collision.h"

namespace Collide
{
    bool isColliding(SDL_Surface* a, int ax, int ay, SDL_Surface* b, int bx, int by){

        float aright = ax + a->w;
        float bright = bx + b->w;
        float abottom = ay + a->h;
        float bbottom = by + b->h;

        if(aright < bx ||bright < ax || bbottom < ay || abottom < by)
            return false;

        float overright  = MIN(aright, bright);
        float overleft   = MAX(ax, bx);
        float overbottom = MIN(abottom, bbottom);
        float overtop    = MAX(ay, by);

        for( int y = overtop; y < overbottom; ++y){
            for(int x = overleft; x < overright; ++x){
                if(!isTransparent(a, x - ax, y - ay) && !isTransparent(b, x - bx, y - by))
                    return true;
            }
        }

        return false;

    }

    bool boundCollide(SDL_Surface* a, int ax, int ay, SDL_Surface* b, int bx, int by){
        if(a && b){
        float aright  = ax + a->w;
        float bright  = bx + b->w;
        float abottom = ay + a->h;
        float bbottom = by + b->h;

        if(aright < bx ||bright < ax || bbottom < ay || abottom < by)
            return false;

        return true;
        }
    }

    bool isColliding(int x, int y, SDL_Surface* surf, int sx, int sy){
        if( x > sx && y > sy && x < sx + surf->w && y < sy + surf->h)
            if(!isTransparent(surf, x - sx, y - sy))
                return true;

        return false;
    }

    bool isColliding(int x, int y, SDL_Rect* r){
        if( x >= r->x && y >= r->y && x <= r->x + r->w && y <= r->y + r->h)
            return true;

        return false;
    }

    bool isColliding(SDL_Rect* Rect, SDL_Surface* surf, int sx, int sy){

        float rright = Rect->x + Rect->w;
        float rbottom = Rect->y + Rect->h;

        if(rright < sx || sx + surf->w < Rect->x || sy + surf->h < Rect->y || rbottom < sy)
            return false;

        float overright = MIN(rright, sx + surf->w);
        float overleft = MAX(Rect->x, sx);
        float overbottom = MIN(rbottom, sy + surf->h);
        float overtop = MAX(Rect->y, sy);

        for( int y = overtop; y < overbottom; ++y){
            for(int x = overleft; x < overright; ++x){
                if(!isTransparent(surf, x - sx, y - sy))
                    return true;

            }
        }

        return false;

    }

    bool isColliding(SDL_Rect* r1, SDL_Rect* r2){

        float aright = r1->x + r1->w;
        float bright = r2->x + r2->w;
        float abottom = r1->y + r1->h;
        float bbottom = r2->y + r2->h;

        if(aright < r2->x || bright < r1->x || bbottom < r1->y || abottom < r2->y)
            return false;

        return true;
    }

    bool isColliding(vector2 p1, vector2 p2, SDL_Rect* box){
        vector2 midLine = (p2 + p1)/2; //mid point of line
        vector2 midBox = vector2(box->x, box->y) + vector2(box->w, box->h)/2; //mid point of box
        vector2 rLine = p2 - midLine; //radius that encompasses line
        vector2 rBox = vector2(box->w, box->h)/2; //radius that emcompasses box
        //Coarse Bounding-Circle Test
        if((midLine-midBox).magnitude() > (rLine.magnitude() + rBox.magnitude())) return false;
        else{
            return true;
            //Separating axis Test for exact collision
            //Build Rects

            CollisionRect A, B;
            A.UL = p1; A.UR = p1 + vector2(1,0);
            A.LR = p2; A.LL = p2 + vector2(1,0);
            B.UL = vector2(box->x-box->w/2, box->y-box->w/2);
            B.UR = vector2(box->x+box->w/2, box->y-box->w/2);
            B.LR = vector2(box->x+box->w/2, box->y+box->w/2);
            B.LL = vector2(box->x-box->w/2, box->y+box->w/2);

            vector2 Axis[4];
            Axis[0] = (A.UR - A.UL);
            Axis[1] = (A.UR - A.LR);
            Axis[2] = (B.UL - B.LL);
            Axis[3] = (B.UL - B.UR);


            for(int i = 0; i < 3; i++){

                GLGraphics::DrawLine(600,600, Axis[i].x+600, Axis[i].y+600, 127,0,0);

                float AUR = scalarProj(A.UR, Axis[i]);
                float AUL = scalarProj(A.UL, Axis[i]);
                float ALR = scalarProj(A.LR, Axis[i]);
                float ALL = scalarProj(A.LL, Axis[i]);

                float BUR = scalarProj(B.UR, Axis[i]);
                float BUL = scalarProj(B.UL, Axis[i]);
                float BLR = scalarProj(B.LR, Axis[i]);
                float BLL = scalarProj(B.LL, Axis[i]);

                Debug::Log("\nAxis ");
                Debug::Log(i);
                Debug::Log("\nMAX B: ");
                Debug::Log(MAX(MAX(BUR,BUL),MAX(BLR,BLL)));
                Debug::Log("\nMIN A: ");
                Debug::Log(MIN(MIN(AUR,AUL),MIN(ALR,ALL)));
                Debug::Log("\nMAX A: ");
                Debug::Log(MAX(MAX(AUR,AUL),MAX(ALR,ALL)));
                Debug::Log("\nMIN B: ");
                Debug::Log(MIN(MIN(BUR,BUL),MIN(BLR,BLL)));



                if(((MAX(MAX(BUR,BUL),MAX(BLR,BLL))) <= (MIN(MIN(AUR,AUL),MIN(ALR,ALL))))) return false;
                if(((MAX(MAX(AUR,AUL),MAX(ALR,ALL))) <= (MIN(MIN(BUR,BUL),MIN(BLR,BLL))))) return false;
            }

            return true;

        }
    }

    bool isColliding(CollisionRect A, float tA, CollisionRect B, float tB){
        rotateRect(&A, tA);
        rotateRect(&B, tB);


        glBegin(GL_QUADS);
            glColor3b(127,0,0);
            glVertex2f(A.UL.x, A.UL.y);
            glVertex2f(A.UR.x, A.UR.y);
            glVertex2f(A.LR.x, A.LR.y);
            glVertex2f(A.LL.x, A.LL.y);
        glEnd();

        glBegin(GL_QUADS);
            glColor3b(127,0,0);
            glVertex2f(B.UL.x, B.UL.y);
            glVertex2f(B.UR.x, B.UR.y);
            glVertex2f(B.LR.x, B.LR.y);
            glVertex2f(B.LL.x, B.LL.y);
        glEnd();


        vector2 midA = (A.UL + A.LR)/2;
        vector2 midB = (B.UL + B.LR)/2;
        float rA = (A.LR - midA).magnitude();
        float rB = (B.LR - midB).magnitude();

        GLGraphics::DrawCircle(midA.x, midA.y, rA, 15, 127,127,127);
        GLGraphics::DrawCircle(midB.x, midB.y, rB, 15, 127,127,127);

        //Coarse Bounding-Circle Test
        if((midA-midB).magnitude() > rA+rB) return false;
        else{
            return true;
            //Separating axis Test for exact collision
            vector2 Axis[4];
            Axis[0] = (A.UR - A.UL);
            Axis[1] = (A.UR - A.LR);
            Axis[2] = (B.UL - B.LL);
            Axis[3] = (B.UL - B.UR);


            for(int i = 0; i < 4; i++){

                float AUR = scalarProj(A.UR, Axis[i]);
                float AUL = scalarProj(A.UL, Axis[i]);
                float ALR = scalarProj(A.LR, Axis[i]);
                float ALL = scalarProj(A.LL, Axis[i]);

                float BUR = scalarProj(B.UR, Axis[i]);
                float BUL = scalarProj(B.UL, Axis[i]);
                float BLR = scalarProj(B.LR, Axis[i]);
                float BLL = scalarProj(B.LL, Axis[i]);

                Debug::Log("\nAxis ");
                Debug::Log(i);
                Debug::Log("\nMAX B: ");
                Debug::Log(MAX(MAX(BUR,BUL),MAX(BLR,BLL)));
                Debug::Log("\nMIN A: ");
                Debug::Log(MIN(MIN(AUR,AUL),MIN(ALR,ALL)));
                Debug::Log("\nMAX A: ");
                Debug::Log(MAX(MAX(AUR,AUL),MAX(ALR,ALL)));
                Debug::Log("\nMIN B: ");
                Debug::Log(MIN(MIN(BUR,BUL),MIN(BLR,BLL)));



//                if(((MAX(MAX(BUR,BUL),MAX(BLR,BLL))) <= (MIN(MIN(AUR,AUL),MIN(ALR,ALL))))) return false;
//                if(((MAX(MAX(AUR,AUL),MAX(ALR,ALL))) <= (MIN(MIN(BUR,BUL),MIN(BLR,BLL))))) return false;
            }

            return true;

        }
    }

    float scalarProj(vector2 u, vector2 a){
        return ((a*(u.dot(a))/pow(a.magnitude(), 2)).dot(a));
    }

    void rotateRect(CollisionRect* Box, float t){
        vector2 midBox = (Box->UL + Box->LR)/2;

        Box->UL -= midBox; //TO OBJECT SPACE!!!
        Box->UR -= midBox;
        Box->LR -= midBox;
        Box->LL -= midBox;

        rotatePoint(&Box->UL, t); //ROTATION MATRIX!!!
        rotatePoint(&Box->UR, t);
        rotatePoint(&Box->LR, t);
        rotatePoint(&Box->LL, t);

        Box->UL += midBox; //BACK TO WORLD SPACE!!!
        Box->UR += midBox;
        Box->LR += midBox;
        Box->LL += midBox;
    }

    void rotatePoint(vector2* p, float t){
        vector2 rotV = vector2(cosf(t), sinf(t));


        p->x = ((p->x*rotV.x) - (p->y*rotV.y));
        p->y = ((p->x*rotV.y) + (p->y*rotV.x));
    }

    bool isTransparent(SDL_Surface* surf, int x, int y){

        SDL_LockSurface(surf);

        Uint32 temp, *pixel;
        Uint8 alpha;

        pixel = ((Uint32*)surf->pixels);

        pixel += (y * surf->w) + x;

        SDL_UnlockSurface(surf);


        temp  = *pixel & surf->format->Amask;
        temp  = temp >> surf->format->Ashift; /* Shift it down to 8-bit */
        temp  = temp << surf->format->Aloss;  /* Expand to a full 8-bit number */
        alpha = (Uint8)temp;


        if(alpha ^ 255 != 0) return false;

        return true;


    }

    int CircleCollide(int ax, int ay, int ar, int bx, int by, int br){
        if(hypot(ax-bx, ay-by)<ar+br) return (ar+br) - hypot(ax-bx, ay-by);
        return false;
    }

}





