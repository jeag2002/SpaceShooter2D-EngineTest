#include "GLGraphics.h"
#include "Particle.h"
#include "GLText.h"
#include "gl2dLight.h"

bool running = true;
bool moving;
float x = 0, y = 0;
int s = 0, d = 0;
GLuint dirt;
vector2 mVel;
void Events();

Obstacle o;
int v = -1;

std::vector<Obstacle> room;
std::vector<Light> lights;

void addPoint(int, int);
void finishShape();
void addLight(int, int, int);

int main(int argc, char** argv){
    //GLGraphics::Init(false);
    GLGraphics::AutoInit();
    Debug::Init();
    Debug::fps = 2500;
    dirt = GLGraphics::Load("dirt.jpg");
    glPointSize(5);
    srand(time(0));
    o.color = vector3(RandInt(0,127),RandInt(0,127),RandInt(0,127)).normalize() * 127;
    o.opacity = 0.f;

    while(running){
        for(int i = 0; i < 16; i++){
            GLGraphics::DrawImage(dirt, (i%4)*256,(i/4)*256,256,256, 10,10,10);
        }

        for(int i = 0; i < lights.size(); i++){
            lights[i].RayCast(&room);
        }
        for(int i = 0; i < room.size(); i++){
            room[i].Draw();
        }



        o.Draw();

        Debug::FPS(10);
        GLGraphics::Flip();
        Events();
        //SDL_Delay(10);
    }
    Debug::Log("While loop terminated");

    return 0;
}

void addPoint(int x, int y){
    v++;
    o.verts.push_back(vector2(x, y));
    if(v > 0){
        o.norms.push_back((o.verts[v] - o.verts[v-1]).perp().normalize());
        o.index.push_back(vector2(v-1, v));
    }
}

void finishShape(){
    o.norms.push_back((o.verts[0] - o.verts[v]).perp().normalize());
    o.index.push_back(vector2(v, 0));


    o.Finalize();

    room.push_back(o);
    o.color = vector3(RandInt(0,127),RandInt(0,127),RandInt(0,127)).normalize() * 127;

    v = -1;

    o.verts.clear();
    o.norms.clear();
    o.index.clear();
    o.pos = vector2(0,0);
}

void addLight(int x, int y, int i){
    Light l(i, vector3(RandInt(0,127),RandInt(0,127),RandInt(0,127)).normalize() * 127);
    //Light l(i, vector3(127,127,127).normalize() * 127);
    l.Pos(vector2(x,y));
    lights.push_back(l);
}

void Events(){
    static SDL_Event Event;
    moving = false;
    while(SDL_PollEvent(&Event)){
        switch(Event.type){
            case SDL_MOUSEMOTION:
                moving = true;
                mVel.x = Event.motion.x - x;
                mVel.y = Event.motion.y - y -100;
                x = Event.motion.x;
                y = Event.motion.y;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(Event.button.button){
                        case SDL_BUTTON_MIDDLE:
                            finishShape();
                            break;
                        case SDL_BUTTON_LEFT:
                            addPoint(x, y);
                            break;
                        case SDL_BUTTON_RIGHT:
                            addLight(x,y,RandInt(50,100));
                            break;
                        case SDL_BUTTON_WHEELUP:
                            for(int i = 0; i < room.size(); i++){
                                room[i].opacity += 0.1f;
                                room[i].opacity = room[i].opacity > .9? .9: room[i].opacity;
                            }
                            break;
                        case SDL_BUTTON_WHEELDOWN:
                            for(int i = 0; i < room.size(); i++){
                                room[i].opacity -= 0.1f;
                                room[i].opacity = room[i].opacity < 0.1 ? 0.1: room[i].opacity;
                            }
                            break;
                        default: break;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    switch(Event.button.button){
                        case SDL_BUTTON_LEFT:
                            break;
                        case SDL_BUTTON_RIGHT:
                            break;
                        default: break;
                    }
                break;
            case SDL_KEYDOWN:
                switch(Event.key.keysym.sym){
                    case SDLK_END: running = false;
                        break;
                    default: break;
                }
                break;
            case SDL_QUIT: running = false;
                break;

            default: break;
        }
    }
}
