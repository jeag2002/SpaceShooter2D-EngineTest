#ifndef GLVERTEX_H_INCLUDED
#define GLVERTEX_H_INCLUDED

struct pVertex
{
    pVertex(float _x, float _y, float _z):x(_x),y(_y),z(_z){}
    float x,y,z;
	float padding[5]; //5*4 = 20 bytes of padding to align with 32 bytes(for ATI)
};


struct ptVertex
{
    ptVertex(float _x, float _y, float _z, float _s0, float _t0):x(_x),y(_y),z(_z),s0(_s0),t0(_t0){}
	float x,y,z; //position
	float s0, t0; //tex coord 0
	float padding[3]; //3*4 = 12 bytes of padding to align with 32 bytes(for ATI)
};


#endif // GLVERTEX_H_INCLUDED

