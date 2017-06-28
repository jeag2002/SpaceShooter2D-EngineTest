/*
CLOCKENGINE_H -> Marca el ritmo de juego. Limita el ritmo a 60fps en entornos Desktop y 30fps en entornos moviles.
//http://gamedev.stackexchange.com/questions/6825/time-based-movement-vs-frame-rate-based-movement
*/

#ifndef CLOCKENGINE_H_INCLUDED
#define CLOCKENGINE_H_INCLUDED

#include "Stdafx.h"

#define DESKTOP_FRAMERRATE 60
#define MOBILE_FRAMERRATE 30

class ClockEngine{

    public:

    ClockEngine(){}
    void SetFrameRate();
    void SetTimeRate();

    private:

    float vSync;

};

#endif // CLOCKENGINE_H_INCLUDED
