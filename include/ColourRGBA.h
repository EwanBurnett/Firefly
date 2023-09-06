#ifndef _FIREFLY_COLOURRGBA_H
#define _FIREFLY_COLOURRGBA_H

#include <cstdint>

namespace Firefly
{
    struct ColourRGBA{
        ColourRGBA(uint8_t R = 0, uint8_t G = 0, uint8_t B = 0, uint8_t A = 255);
        uint8_t r, g, b, a;
    };

    inline ColourRGBA::ColourRGBA(uint8_t R, uint8_t G, uint8_t B, uint8_t A){
        r = R;
        g = G;
        b = B;
        a = A;
    }
}

#endif
