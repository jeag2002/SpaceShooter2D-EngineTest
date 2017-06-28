//Vector class with appropriate operators overloaded.
//written with minimum line count in mind. *not real easily read*
//Patrick Oyarzun

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class vector3{
public:
    vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) : x(X),y(Y),z(Z){};
    ~vector3(){};

    vector3& operator=(const vector3 &rhs) {
        x=rhs.x;
        y=rhs.y;
        z=rhs.z;
        return *this;
    }

    vector3  operator+(const vector3 &rhs) {
        return vector3(x+rhs.x, y+rhs.y, z+rhs.z);
    }
    vector3  operator+(const float &rhs) {
        return vector3(x+rhs, y+rhs, z+rhs);
    }
    vector3& operator+=(const vector3 &rhs){
        x+=rhs.x;
        y+=rhs.y;
        z+=rhs.z;
        return *this;
    }

    vector3  operator-(const vector3 &rhs) {
        return vector3(x-rhs.x, y-rhs.y, z-rhs.z);
    }
    vector3  operator-(const float &rhs) {
        return vector3(x-rhs, y-rhs, z-rhs);
    }
    vector3& operator-=(const vector3 &rhs){
        x-=rhs.x;
        y-=rhs.y;
        z-=rhs.z;
        return *this;
    }

    vector3& operator*=(const float &rhs){
        x*=rhs;
        y*=rhs;
        z*=rhs;
        return *this;
    }
    vector3  operator*(const float &rhs) {
        return vector3(x*rhs, y*rhs, z*rhs);
    }
    vector3  operator/(const float &rhs) {
        return vector3(x/rhs, y/rhs, z/rhs);
    }

    float magnitude(){
        return hypotf(hypotf(x, y), z);
    }

    float dot(vector3 rhs){
        return float(x*rhs.x+y*rhs.y+z*rhs.z);
    }

    vector3 normalize(){
        return vector3(x/magnitude(),y/magnitude(),z/magnitude());
    }


    float x, y, z;
};

#endif
