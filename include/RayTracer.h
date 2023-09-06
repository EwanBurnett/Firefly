#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include "Vector3.h"
#include "ColourRGBA.h"
#include "Ray3D.h"

#include <cstdio>

namespace Firefly{

    inline bool HitSphere(const Vector3& center, float radius, const Ray3D& ray)
    {
        Vector3 oc = ray.Origin() - center;
        float a = Vector3::Dot(ray.Direction(), ray.Direction());
        float b = 2.0f * Vector3::Dot(oc, ray.Direction());
        float c = Vector3::Dot(oc, oc) - (radius * radius);

        float discriminant = (b * b) - (4.0f * (a * c));

        //printf("Ray:\n\tDir = (%f, %f, %f)\n\tOrigin = (%f, %f, %f)\nOrigin -> Center = (%f, %f, %f)\n\ta = %f\n\tb = %f\n\tc = %f\n\tDiscriminant = %f\n\t", ray.Direction().x, ray.Direction().y, ray.Direction().z, ray.Origin().x, ray.Origin().y, ray.Origin().z, oc.x, oc.y, oc.z, a, b, c, discriminant);


        return (discriminant >= 0.0f);
    }

    inline ColourRGBA RayColour(const Ray3D& ray){
        
        if(HitSphere(Vector3(0.0f, 0.0f, -1.0f), 0.5f, ray)){
            return ColourRGBA(255, 0, 0, 255);
        }

        Vector3 dir = ray.Direction();
        auto k = 0.5f * (dir.y + 1.0f);
        auto a = ColourRGBA{190, 255, 65, 180};
        auto b = ColourRGBA{255, 128, 196, 255};

        return{
            (uint8_t)(((1.0f - k) * a.r + k * b.r)),
            (uint8_t)(((1.0f - k) * a.g + k * b.g)),
            (uint8_t)(((1.0f - k) * a.b + k * b.b)),
            (uint8_t)(((1.0f - k) * a.a + k * b.a)),
        };
    }
}
#endif
