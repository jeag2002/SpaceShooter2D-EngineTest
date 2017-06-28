#include "Particle.h"

ParticleSystem::~ParticleSystem(){p.clear();}
void ParticleSystem::Init(){}
void ParticleSystem::Timer(float t){timer = t; timerActive = true;}
void ParticleSystem::Pos(vector2 p){pos = p;}
void ParticleSystem::Update(float, vector2){}
void ParticleSystem::Render(float){}
void ParticleSystem::Spawn(){}

//Radial Emiter useful for explosions
RadialEmiter::~RadialEmiter(){
    p.clear();
}

void RadialEmiter::Init(float l, float f, float v, vector3 c1, vector3 c2){
    timerActive = false;
    life = l;
    flow = f;
    velocity = v;
    maxParticles = l*f;
    color2 = c2;
    color1 = c1;
    Particle temp(vector2(0.f,0.f), vector2(0.f,0.f), 0.f, vector3(0.f,0.f,0.f));
    if(p.size() != maxParticles) p.resize(maxParticles, temp);
}

void RadialEmiter::Update(float dt){
//    if(timerActive)if((timer-=dt) > 0) Spawn(dt, l); //revive 'dead' particles at (flow) particles per second
//    if(!timerActive)Spawn(dt, l);

    for(int i = 0; i < p.size(); ++i){
        if(p[i].pos.x < 0 || p[i].pos.x > GLGraphics::winW) p[i].life = 0;
        if(p[i].pos.y < 0 || p[i].pos.y > GLGraphics::winH) p[i].life = 0;
        p[i].pos += p[i].vel * dt;
        p[i].life -= dt;
        p[i].color = color2 + ((color1 - color2)*float(p[i].life/life));
    }
}

void RadialEmiter::Render(){
    glBindTexture(GL_TEXTURE_2D, NULL); GLGraphics::boundTexture = NULL;

    Debug::Caption(p.size());
    int s = 1;
    int d = 10;
    int r = 1;
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    for(int i = 0; i < 5; i++){
        glPointSize(i*s*2);
        glBegin(GL_POINTS);
            for(int i = 0; i < p.size(); ++i){
                if((p[i].life) > 0){ //if particle is not dead
                    glColor3b(p[i].color.x/d, p[i].color.y/d, p[i].color.z/d);
                    glVertex2f(p[i].pos.x,p[i].pos.y);
                }
            }
        glEnd();
    }

    glPointSize(s);
    glBegin(GL_POINTS);


        for(int i = 0; i < p.size(); ++i){
            if((p[i].life) > 0){ //if particle is not dead
                //draw particle
                glColor3b(p[i].color.x, p[i].color.y, p[i].color.z);
                glVertex2f(p[i].pos.x,p[i].pos.y);
//                glVertex2f(p[i].pos.x-r,p[i].pos.y-r);
//                glVertex2f(p[i].pos.x+r,p[i].pos.y-r);
//                glVertex2f(p[i].pos.x+r,p[i].pos.y+r);
//                glVertex2f(p[i].pos.x-r,p[i].pos.y+r);

            }
        }
    glEnd();

    glPopMatrix();
}

void RadialEmiter::Spawn(float dt, vector2 l, vector2 vs){
    static float count; // max that should be spawned this frame
    static float deg, v;
    count += flow*dt; //round up(else powerhouse pcs will never spawn)
    for(int i = 0; i < p.size(); ++i){
        if(p[i].life <= 0 && count >= 1){
            //re-init particle
            p[i].pos = vector2(l.x,l.y);
            deg = RandFloat()*(2*PI);
            v = RandInt(velocity/2,velocity);
            p[i].vel = vs + vector2(cosf(deg)*v, sinf(deg)*v);
            p[i].life = life;
            p[i].color = color2;

            count--;
        }
    }
}

FieldEmiter::~FieldEmiter(){}

void FieldEmiter::Init(float f, int size, vector3 c, vector2 ul, vector2 lr){
    bound.x = ul.x;
    bound.y = ul.y;
    bound.w = lr.x-ul.x;
    bound.h = lr.y-ul.y;
    timerActive = false;
    maxParticles = f;
    color1 = c;
    Particle temp(vector2(0.f,0.f), vector2(0.f,0.f), 0.f, vector3(0.f,0.f,0.f));
    if(p.size() != maxParticles) p.resize(maxParticles, temp);
    Spawn();
    s = size;
}

void FieldEmiter::Update(float dt){
    for(int i = 0; i < p.size(); ++i){
        p[i].pos += p[i].vel * dt;

        if(p[i].pos.x < bound.x){ p[i].vel.x *= -res; p[i].pos.x = bound.x;}
        if(p[i].pos.x > bound.x + bound.w){ p[i].vel.x *= -res; p[i].pos.x = bound.x + bound.w;}
        if(p[i].pos.y < bound.y){ p[i].vel.y *= -res; p[i].pos.y = bound.y;}
        if(p[i].pos.y > bound.y + bound.h){ p[i].vel.y *= -res; p[i].pos.y = bound.y + bound.h;}
    }
}

void FieldEmiter::Pull(vector2 loc, float str){
    for(int i = 0; i < p.size(); i++){
        static float d;
        d = atanf((p[i].pos.y-loc.y)/(p[i].pos.x-loc.x));
        if((p[i].pos.x-loc.x) > 0) d = PI + d;

        p[i].vel+=vector2(cosf(d)*str, sinf(d)*str);

    }
}

void FieldEmiter::Push(vector2 loc, float str){
    for(int i = 0; i < p.size(); i++){
        static float d;
        d = atanf((p[i].pos.y-loc.y)/(p[i].pos.x-loc.x));
        if((p[i].pos.x-loc.x) > 0) d = PI + d;

        p[i].vel-=vector2(cosf(d)*str, sinf(d)*str);

    }
}

void FieldEmiter::Render(){
    glBindTexture(GL_TEXTURE_2D, NULL); GLGraphics::boundTexture = NULL;

    Debug::Caption(p.size());
    int d = 10;
    int r = 1;
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    for(int i = 0; i < 5; i++){
        glPointSize(i*s);
        glBegin(GL_POINTS);
            for(int i = 0; i < p.size(); ++i){
                glColor3b(p[i].color.x/d, p[i].color.y/d, p[i].color.z/d);
                glVertex2f(p[i].pos.x,p[i].pos.y);
            }
        glEnd();
    }

    glPointSize(s);
    glBegin(GL_POINTS);


        for(int i = 0; i < p.size(); ++i){
                //draw particle
            glColor3b(p[i].color.x/d, p[i].color.y/d, p[i].color.z/d);
            glVertex2f(p[i].pos.x,p[i].pos.y);

        }
    glEnd();

    glPopMatrix();
}

void FieldEmiter::Spawn(){
    static float count;
    static float x, y;
    count = sqrt(maxParticles);
    x = bound.w/count;
    y = bound.h/count;
    for(int i = 0; i < p.size(); i++){
            p[i].pos = vector2((i%int(count)) * x, (i/count) * y);
            p[i].vel = vector2(0,0);
            p[i].color = color1;
    }
}

////Beam Emiter useful for lasers
//BeamEmiter::~BeamEmiter(){
//    p.clear();
//}
//
//void BeamEmiter::Init(float l, float f, vector3 c){
//    life = l;
//    flow = f;
//    maxParticles = l*f;
//    color = c;
//    Particle temp(vector2(0.f,0.f), vector2(0.f,0.f), 0.f, vector3(0.f,0.f,0.f));
//    if(p.size() != maxParticles) p.resize(maxParticles, temp);
//}
//void BeamEmiter::Render(float dt, vector2 s, vector2 e){
//    Spawn(dt, s, e); //revive 'dead' particles at (flow) particles per second
//
//    glPushMatrix();
//    glBegin(GL_QUADS);
//
//        for(int i = 0; i < p.size(); ++i){
//            if((p[i].life -= dt) > 0){ //if particle is not dead
//                //update particle
//                p[i].pos += p[i].vel * dt;
//                p[i].color -= vector3(dt,dt,dt);
//                //draw particle
//                glcolor2b(p[i].color.x, p[i].color.y, p[i].color.z);
//                glVertex2f(p[i].pos.x-1,p[i].pos.y-1);
//                glVertex2f(p[i].pos.x+1,p[i].pos.y-1);
//                glVertex2f(p[i].pos.x+1,p[i].pos.y+1);
//                glVertex2f(p[i].pos.x-1,p[i].pos.y+1);
//
//            }
//        }
//    glEnd();
//    glPopMatrix();
//}
//
//void BeamEmiter::Spawn(float dt, vector2 s, vector2 e){
//    for(int i = 0; i < p.size(); ++i){
//        if(p[i].life <= 0){
//            //re-init particle
//        }
//    }
//}
//
//Spray Emiter useful for sparks/fountains
SprayEmiter::~SprayEmiter(){
    p.clear();
}

void SprayEmiter::Init(float l, float f, float v, vector3 c1, vector3 c2){
    timerActive = false;
    life = l;
    flow = f;
    velocity = v;
    maxParticles = l*f;
    color2 = c2;
    color1 = c1;
    Particle temp(vector2(0.f,0.f), vector2(0.f,0.f), 0.f, vector3(0.f,0.f,0.f));
    if(p.size() != maxParticles) p.resize(maxParticles, temp);
}

void SprayEmiter::Update(float dt, vector2 l, float t){
    if(timerActive)if((timer-=dt) > 0) Spawn(dt, l, t); //revive 'dead' particles at (flow) particles per second
    if(!timerActive)Spawn(dt, l, t);;
    Spawn(dt, l, t);

    for(int i = 0; i < p.size(); ++i){
        p[i].life -= dt*10;
        //update particle
        p[i].pos += p[i].vel * dt;
        p[i].color = color2 + ((color1 - color2)*float(p[i].life/life));
    }
}

void SprayEmiter::Render(){
    glBegin(GL_POINTS);

        for(int i = 0; i < p.size(); ++i){
            if(p[i].life > 0){ //if particle is not dead
                //draw particle
                glColor3b(p[i].color.x, p[i].color.y, p[i].color.z);
                glVertex2f(p[i].pos.x,p[i].pos.y);
            }
        }
    glEnd();
}

void SprayEmiter::Spawn(float dt, vector2 l, float t){
    static int count; // max that should be spawned this frame
    static float deg, v;
    count = flow*dt;
    //count /= 2;
    for(int i = 0; i < p.size(); ++i){
        if(p[i].life <= life/2 && count >= 0){
            //re-init particle
            p[i].pos = l;
            deg = t*(PI/180);
            v = RandInt(velocity/2,velocity);
            p[i].vel = vector2(cosf(deg)*v, sinf(deg)*v);
            p[i].life = life;
            p[i].color = color2;

            count--;
        }
    }
}
