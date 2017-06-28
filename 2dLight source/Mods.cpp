#include "Mods.h"

Mod::Mod(vector2 _pos, vector2 _size, int _r, int _g, int _b, int _a):
    off(_pos),
    size(_size),
    r(_r),
    g(_g),
    b(_b),
    a(_a){}

Mod::~Mod(){}

void Mod::Set(unsigned int flag, float n){
    switch(flag & SET_MASK){
        case X_POS:
                off.x = n;
            break;
        case Y_POS:
                off.y = n;
            break;
        case ROT:
                relT = n;
            break;
        case R_COLOR:
                r = n;
            break;
        case G_COLOR:
                g = n;
            break;
        case B_COLOR:
                b = n;
            break;
        case A_COLOR:
                a = n;
            break;
        case TEXTURE:
                texture = n;
            break;
        case X_SIZE:
                size.x = n;
            break;
        case Y_SIZE:
                size.y = n;
            break;
        default: break;
    }
}

float Mod::Get(unsigned int flag){
    switch(flag & SET_MASK){
        case X_POS:
                return off.x;
            break;
        case Y_POS:
                return off.y;
            break;
        case ROT:
                return relT;
            break;
        case R_COLOR:
                return r;
            break;
        case G_COLOR:
                return g;
            break;
        case B_COLOR:
                return b;
            break;
        case A_COLOR:
                return a;
            break;
        case TEXTURE:
                return texture;
            break;
        case X_SIZE:
                return size.x;
            break;
        case Y_SIZE:
                return size.y;
            break;
        default: break;
    }
}

void Mod::OnEvent(SDL_Event* Event, float dt){
    switch(Event->type){
        case SDL_KEYDOWN:
                printf("\n%d :: %d pressed!", SDL_GetTicks(), Event->key.keysym.sym);
            break;
        default: break;
    }
}

int Mod::Update(int, int, int, float){}

void Mod::Draw(){
    printf("\n%d :: ... draw call was made, did you forget to overide Draw()?", SDL_GetTicks());
}

void Mod::CheckCollide(BulletManager*, float){}

void Mod::OnCollide(){}

void Mod::AI(vector2){}
