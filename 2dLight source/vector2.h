#ifndef vector2_H
#define vector2_H

#include <cmath>

class vector2{
public:
    vector2(float X = 0.0f, float Y = 0.0f) : x(X),y(Y){};
    ~vector2(){};

    vector2& operator=(const vector2 &rhs) {
        x=rhs.x;
        y=rhs.y;
        return *this;
    }

    vector2  operator+(const vector2 &rhs) {
        return vector2(x+rhs.x, y+rhs.y);
    }
    vector2  operator+(const float &rhs) {
        return vector2(x+rhs, y+rhs);
    }
    vector2& operator+=(const vector2 &rhs){
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }

    vector2  operator-(const vector2 &rhs) {
        return vector2(x-rhs.x, y-rhs.y);
    }
    vector2  operator-(const float &rhs) {
        return vector2(x-rhs, y-rhs);
    }
    vector2& operator-=(const vector2 &rhs){
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }

    vector2& operator*=(const float &rhs){
        x*=rhs;
        y*=rhs;
        return *this;
    }
    vector2  operator*(const float &rhs) {
        return vector2(x*rhs, y*rhs);
    }
    vector2  operator/(const float &rhs) {
        return vector2(x/rhs, y/rhs);
    }
    vector2 operator*(const vector2 &rhs){
        return vector2(x*rhs.x,y*rhs.y);
    }
    vector2 operator/(const vector2 &rhs){
        return vector2(x/rhs.x,y/rhs.y);
    }

    float magnitude(){
        return hypotf(x, y);
    }

    float dot(vector2 rhs){
        return float(x*rhs.x+y*rhs.y);
    }

    vector2 normalize(){
        return vector2(x/magnitude(),y/magnitude());
    }

    vector2 perp(){
        return vector2(y,-x);
    }


    float x, y;
};

#endif //VECTOR2_H
