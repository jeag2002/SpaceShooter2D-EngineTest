#ifndef GL_2D_LIGHT
#define GL_2D_LIGHT

#include "GLGraphics.h"
#include "Debug.h"
#include "GLText.h"
#include "vector2.h"
#include "vector3.h"
#include <vector>

struct Obstacle{
    void Draw(){
        //glDisable(GL_BLEND);
        glBindTexture(GL_TEXTURE_2D, NULL); GLGraphics::boundTexture = NULL;
        glBegin(GL_POLYGON);
        glColor3b(color.x*(1-opacity),color.y*(1-opacity),color.z*(1-opacity));
        for(int i = 0; i < verts.size(); i++){
            glVertex2f(pos.x + verts[i].x, pos.y + verts[i].y);
        }
        glEnd();
        //glEnable(GL_BLEND);
    }
    void Finalize(){ //calc position
        static vector2 t;
        t = vector2(0,0);
        for(int i = 0; i < verts.size(); i++){
            t += verts[i];
        }
        t = t/verts.size();

        pos = t;
        for(int i = 0; i < verts.size(); i++){
            verts[i] -= pos;
        }
    }
    std::vector<vector2> verts;
    std::vector<vector2> index;
    std::vector<vector2> norms;
    vector3 color;
    vector2 pos;
    float opacity;
};

class Light
{
	public:
		Light(float, vector3);
		~Light();
		void RayCast(std::vector<Obstacle>*);
		void Pos(vector2);
		vector2 Pos();
	private:
        float intensity;
        vector2 pos;
        vector2 vel;
        vector3 color;
};

//struct Fire{
//    Fire(vector2 _p){
//        p = _p; f = 1; z = 0;
//        flame.Init(1, 50, 15, vector3(127,127,0), vector3(127,32,32));
//    }
//    void Update(){
//
//
//        if(f) z--;
//        else z++;
//
//        if(RandFloat() > 0.1f) f ^= 1;
//
//        z = z>5? 5: z;
//        z = (z<3)? 3 : z;
//
//        flame.Update(1/Debug::fps);
//        flame.Spawn(1/Debug::fps, p, vector2(0,-20));
//        flame.Render();
//
//        GLGraphics::DrawImage(light, p.x-128,p.y-128,256,256, z*10, z*5, 0);
//    }
//    RadialEmiter flame;
//    vector2 p;
//    bool f;
//    float z;
//};


#endif // GL_2D_LIGHT

