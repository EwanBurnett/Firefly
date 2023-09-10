#ifndef _FIREFLY_COLOURRGBA_H
#define _FIREFLY_COLOURRGBA_H

#include <cstdint>

namespace Firefly
{

    struct ColourRGBA; 

    struct Colour{
        Colour(float R = 0.0f, float G = 0, float B = 0.0f, float A = 1.0f);
        Colour(const ColourRGBA& colour);

        float r, g, b, a;
    };

        struct ColourRGBA{
        ColourRGBA(uint8_t R = 0, uint8_t G = 0, uint8_t B = 0, uint8_t A = 255);
        ColourRGBA(const Colour& colour);

        uint8_t r, g, b, a;
    };

    }

#endif
