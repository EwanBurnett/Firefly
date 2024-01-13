#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include <cmath>
#include "Vector3.h"
#include "ColourRGBA.h"
#include "Ray3D.h"

#include <cstdio>

namespace Firefly{

    inline float HitSphere(const Vector3& center, float radius, const Ray3D& ray)
    {
        Vector3 oc = ray.Origin() - center;

        //float a = Vector3::Dot(ray.Direction(), ray.Direction());
        //float b = 2.0f * Vector3::Dot(oc, ray.Direction());
        //float c = Vector3::Dot(oc, oc) - (radius * radius);

        //float discriminant = (b * b) - (4.0f * (a * c));

        float a = ray.Direction().LengthSquared();
        float half_b = Vector3::Dot(oc, ray.Direction());
        float c = oc.LengthSquared() - (radius * radius);
        float discriminant = (half_b * half_b) - a * c;

        if(discriminant < 0){
            return -1.0f;
        }
        else{
            //return (-b - sqrt(discriminant)) / (2.0f * a);
            return (-half_b - sqrt(discriminant)) / a;
        }
        

        return (discriminant >= 0.0f);
    }

    inline ColourRGBA RayColour(const Ray3D& ray){
        
        float t = (HitSphere(Vector3(0.0f, 0.0f, -1.0f), 0.5f, ray));
        if(t > 0.0f){
            Vector3 v = (ray.At(t) - Vector3(0.0f, 0.0f, -1.0f));
            Vector3 N = Vector3::Normalize(v);
            ColourRGBA c = {
                (uint8_t)(255.99f * (0.5f * (N.x + 1))),
                (uint8_t)(255.99f * (0.5f * (N.y + 1))),
                (uint8_t)(255.99f * (0.5f * (N.z + 1))),
                255
            };
            return c;
        }

        Vector3 dir = ray.Direction();
        auto k = 0.5f * (dir.y + 1.0f);
        auto a = ColourRGBA{0x9e, 0x33, 0x4a, 180};
        auto b = ColourRGBA{0x0d, 0x56, 0x9e, 255};

        return{
            (uint8_t)(((1.0f - k) * a.r + k * b.r)),
            (uint8_t)(((1.0f - k) * a.g + k * b.g)),
            (uint8_t)(((1.0f - k) * a.b + k * b.b)),
            (uint8_t)(((1.0f - k) * a.a + k * b.a)),
        };
    }
}
#endif
