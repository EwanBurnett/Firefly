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

        float Hit(const Ray3D& ray) override
        {
            Vector3 oc = ray.Origin() - m_Position;

            float a = ray.Direction().LengthSquared();
            float half_b = Vector3::Dot(oc, ray.Direction());
            float c = oc.LengthSquared() - (m_Radius * m_Radius);
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
