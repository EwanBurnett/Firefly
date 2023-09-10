#ifndef _FIREFLY_MATH_HELPER_H
#define _FIREFLY_MATH_HELPER_H

#include <cmath>
#include <limits>
#include <cstdint>

namespace Firefly
{

    //CONSTANTS
    const float PI = 3.1415926535897932385;
    const float Infinity = std::numeric_limits<float>::infinity(); 

    inline float DegToRad(float degrees){
        return degrees * (PI / 180.0f);
    }

    inline float RadToDeg(float radians){
        return radians * (180.0f / PI); 
    }
        
    
}

#endif
