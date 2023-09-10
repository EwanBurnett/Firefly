#include "../include/ColourRGBA.h"

using namespace Firefly; 

Colour::Colour(float R, float G, float B, float A){
        r = R;
        g = G;
        b = B;
        a = A;
    }

Colour::Colour(const ColourRGBA& colour){
        r = colour.r / 255.99f;
        g = colour.g / 255.99f;
        b = colour.b / 255.99f;
        a = colour.a / 255.99f;
    }

ColourRGBA::ColourRGBA(uint8_t R, uint8_t G, uint8_t B, uint8_t A){
        r = R;
        g = G;
        b = B;
        a = A;
    }
    
ColourRGBA::ColourRGBA(const Colour& colour){
        r = (uint8_t)(colour.r * 255.99f); 
        g = (uint8_t)(colour.g * 255.99f); 
        b = (uint8_t)(colour.b * 255.99f); 
        a = (uint8_t)(colour.a * 255.99f); 

    }

