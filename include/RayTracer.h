#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include "Vector3.h"
#include "ColourRGBA.h"
#include "Ray3D.h"

#include <cstdio>

namespace Firefly{
    inline ColourRGBA RayColour(const Ray3D& ray){
        Vector3 dir = ray.Direction();
        dir = Vector3::Normalize(dir);

        auto k = 0.5f * (dir.y + 1.0f);
        auto a = ColourRGBA{255, 255, 255, 255};
        auto b = ColourRGBA{255, 128, 196, 255};

        return{
            (uint8_t)(255.99f * (1.0f - k) * a.r + k * b.r),
            (uint8_t)(255.99f * (1.0f - k) * a.g + k * b.g),
            (uint8_t)(255.99f * (1.0f - k) * a.b + k * b.b),
            (uint8_t)(255.99f * (1.0f - k) * a.a + k * b.a),
        };
    }
}
#endif
