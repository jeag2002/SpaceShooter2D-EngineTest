#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "vector2.h"
#include "vector3.h"
#include "GLGraphics.h"
#include "Debug.h"
#include "Util.h"
#include <deque>
#include <algorithm>

#define res 0.5

struct Particle
{
    Particle(vector2 p, vector2 v, float l, vector3 c){
        pos = p;
        vel = v;
        life = l;
        color = c;
    }
    vector2 pos, vel;
    float life;
    vector3 color;
};

class ParticleSystem{
    public:
        virtual ~ParticleSystem();
        virtual void Init();
        void Timer(float);
        void Pos(vector2);
        virtual void Update(float, vector2);
        virtual void Render(float);
        float timer;
    protected:
        virtual void Spawn();
        bool timerActive;
        std::deque<Particle> p;
        int maxParticles;
        float life, flow, velocity;
        vector3 color1;
        vector3 color2;
        vector2 pos;
};

class RadialEmiter : public ParticleSystem{
    public:
        ~RadialEmiter();
        void Init(float, float, float, vector3, vector3);
        void Update(float);
        void Render();
        void Spawn(float dt, vector2 l, vector2 vs);
};

class FieldEmiter: public ParticleSystem{
    public:
        ~FieldEmiter();
        void Init(float, int, vector3, vector2, vector2);
        void Update(float);
        void Render();
        void Pull(vector2, float);
        void Push(vector2, float);
        void Spawn();//one time
        SDL_Rect bound;
        int s;
};

//class BeamEmiter : public ParticleSystem{
//    public:
//        ~BeamEmiter();
//        void Init(float, float, vector3);
//        void Render(float dt, vector2 s, vector2 e);
//    private:
//        void Spawn(float dt, vector2 s, vector2 e);
//};

class SprayEmiter : public ParticleSystem{
    public:
        ~SprayEmiter();
        void Init(float, float, float, vector3, vector3);
        void Update(float, vector2 l = vector2(0.f, 0.f), float t = 0.f);
        void Render();
    private:
        void Spawn(float dt, vector2 l, float);
};


#endif // PARTICLE_H_INCLUDED
