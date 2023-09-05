#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include "Vector3.h"
#include "ColourRGBA.h"
#include "Ray3D.h"

#include <cstdio>

namespace Firefly{
    inline ColourRGBA RayColour(const Ray3D& ray){
        Vector3 dir = ray.Direction();
        //dir = Vector3::Normalize(dir);

        printf("\ndir = %f, %f, %f", dir.x, dir.y, dir.z);
        

        auto a = 0.5f * (dir.y + 1.0f);
        auto k = (1.0f - a);
        auto c = ColourRGBA{255, 128, 196, 255};

        return{
            (uint8_t)(255.99 * (k * 1.0f + a * c.r)),
            (uint8_t)(255.99 * (k * 1.0f + a * c.g)),
            (uint8_t)(255.99 * (k * 1.0 + a * c.b)),
            (uint8_t)(255.99 * (k * 1.0 + a * c.a))
        };
    }
}
#endif
