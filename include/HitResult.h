#ifndef _FIREFLY_HIT_RESULT_H
#define _FIREFLY_HIT_RESULT_H

#include "Ray3D.h"
#include "Vector3.h"
#include "MathHelper.h"
#include <memory>

namespace Firefly
{
    class IMaterial; 

    struct HitResult
    {
        HitResult(){
            Point = {};
            Normal = {};
            t = -Infinity;
            isFrontFacing = false; 
            Material = nullptr;
        }

        void SetFaceNormal(const Ray3D& ray, const Vector3& outwardsNormal){
            isFrontFacing = Vector3::Dot(ray.Direction(), outwardsNormal) < 0.0f;
            Normal = isFrontFacing ? outwardsNormal : -outwardsNormal; 
        }

        Vector3 Point;
        Vector3 Normal;
        float t;
        bool isFrontFacing;
        std::shared_ptr<IMaterial> Material;
    };
}


#endif
