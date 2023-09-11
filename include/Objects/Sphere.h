#ifndef _FIREFLY_OBJECT_SPHERE_H
#define _FIREFLY_OBJECT_SPHERE_H

#include "../Object.h"
#include "../Vector3.h"
#include "../Ray3D.h"
#include <cmath>

namespace Firefly
{
    class Sphere : public IObject
    {
    public:
        Sphere(const Vector3& position, float radius);

        bool Hit(const Ray3D& ray, Interval interval, HitResult& result) override
        {
            Vector3 oc = ray.Origin() - m_Position;

            float a = ray.Direction().LengthSquared();
            float half_b = Vector3::Dot(oc, ray.Direction());
            float c = oc.LengthSquared() - (m_Radius * m_Radius);
            float discriminant = (half_b * half_b) - a * c;

            if(discriminant < 0){
                return false;
            }

            //return (-half_b - sqrt(discriminant)) / a;
            float sqrtD = sqrt(discriminant);

            //Find the nearest root that lies within the acceptable range
            float root = (-half_b - sqrtD) / a;
            if(!interval.Surrounds(root)){
                root = (-half_b + sqrtD) / a; 
                if(!interval.Surrounds(root)){
                    return false; 
                }
            }

            result.t = root; 
            result.Point = ray.At(root);
            Vector3 outwardsNormal = (result.Point - m_Position) / m_Radius; 

            result.SetFaceNormal(ray, outwardsNormal);

        
            return true;
        }

    private:
        Vector3 m_Position;
        float m_Radius; 

    };

    inline Sphere::Sphere(const Vector3& position, float radius){
        m_Position = position;
        m_Radius = radius;
    }
}

#endif
