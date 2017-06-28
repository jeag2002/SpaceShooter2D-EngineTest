#include "gl2dLight.h"

Light::Light(float i, vector3 c){
    intensity = i;
    color = c;
    static int r;
    while(!(r = RandInt(-1,1)));
    vel = vector2(100,100)*r;
}

Light::~Light(){}

void Light::RayCast(std::vector<Obstacle>* o){
    pos += vel/Debug::fps;
    if(pos.x < 0) vel.x = 100;
    if(pos.x > GLGraphics::winW) vel.x = -100;
    if(pos.y < 0) vel.y = 100;
    if(pos.y > GLGraphics::winH) vel.y = -100;

    static GLuint light = GLGraphics::Load("spot.jpg");
    GLGraphics::RendertoTexture();
    GLGraphics::DrawImage(light, pos.x-(intensity*10),pos.y-(intensity*10),intensity*20,intensity*20, color.x, color.y, color.z);

    for(int i = 0; i < o->size(); i++){
        for(int j = 0; j < (*o)[i].index.size(); j++){
            //current vertex (*o)[i].verts[j]
            static float d;
            static char s[255];
            static vector2 surf;
            static vector2 ray;
            static vector2 snorm;
            static vector3 scolor;

            surf = (*o)[i].pos + ((*o)[i].verts[(*o)[i].index[j].x]+(*o)[i].verts[(*o)[i].index[j].y])/2; //midpoint of surface
            ray = pos - surf; //light ray
            snorm = (*o)[i].norms[(*o)[i].index[j].x]; //surface normal

            d = snorm.dot(ray); //dot product of surface normal and light ray

            if(d < 0){ //if d < 0: surface is obscured, and shadow must be drawn
                scolor.x = (int(color.x) & int((*o)[i].color.x)) * (*o)[i].opacity; if(scolor.x < 0) scolor.x = 0;
                scolor.y = (int(color.y) & int((*o)[i].color.y)) * (*o)[i].opacity; if(scolor.y < 0) scolor.y = 0;
                scolor.z = (int(color.z) & int((*o)[i].color.z)) * (*o)[i].opacity; if(scolor.z < 0) scolor.z = 0;
                glDisable(GL_BLEND);
                GLGraphics::UnbindTex();
                glBegin(GL_QUADS);
                    glColor3b(scolor.x,scolor.y,scolor.z);
                    glVertex2f((*o)[i].pos.x + (*o)[i].verts[(*o)[i].index[j].x].x,
                               (*o)[i].pos.y + (*o)[i].verts[(*o)[i].index[j].x].y);
                    ray = pos - (*o)[i].verts[(*o)[i].index[j].x] - (*o)[i].pos;
                    ray = ray.normalize();
                    ray = ray * vector2(GLGraphics::winW, GLGraphics::winH);
                    glVertex2f((*o)[i].pos.x + (*o)[i].verts[(*o)[i].index[j].x].x - ray.x,
                               (*o)[i].pos.y + (*o)[i].verts[(*o)[i].index[j].x].y - ray.y);
                    ray = pos - (*o)[i].verts[(*o)[i].index[j].y] - (*o)[i].pos;
                    ray = ray.normalize();
                    ray = ray * vector2(GLGraphics::winW, GLGraphics::winH);
                    glVertex2f((*o)[i].pos.x + (*o)[i].verts[(*o)[i].index[j].y].x - ray.x,
                               (*o)[i].pos.y + (*o)[i].verts[(*o)[i].index[j].y].y - ray.y);
                    glVertex2f((*o)[i].pos.x + (*o)[i].verts[(*o)[i].index[j].y].x,
                               (*o)[i].pos.y + (*o)[i].verts[(*o)[i].index[j].y].y);
                glEnd();
                glEnable(GL_BLEND);
            }

            glBegin(GL_LINES);
                glColor3b(127,0,0);
                glVertex2f(surf.x, surf.y);
                glVertex2f(surf.x+snorm.x*10, surf.y+snorm.y*10);
            glEnd();


        }

    }
    GLGraphics::DrawCircle(pos.x, pos.y, 5, 8, color.x,color.y,color.z);
    GLGraphics::RendertoBackBuffer();
    GLGraphics::DrawImage(GLGraphics::textureFramebufferTexture, 0,GLGraphics::winH,GLGraphics::winW, -GLGraphics::winH);
}

void Light::Pos(vector2 p){
    pos = p;
}

vector2 Light::Pos(){
    return pos;
}
