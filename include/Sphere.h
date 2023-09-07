#ifndef _FIREFLY_SPHERE_H
#define _FIREFLY_SPHERE_H

#include "Renderable.h"

namespace Firefly
{
    class Sphere : public IRenderable
    {
        public:
            Sphere(Vector3 center, float radius);

            bool IsHit(const Ray3D& ray, float t_min, float t_max, HitResult& result) override;
        private:
            Vector3 m_Center;
            float m_Radius;
    };

    inline Sphere::Sphere(Vector3 center, float radius){
        m_Center = center;
        m_Radius = radius;
    }

    inline bool Sphere::IsHit(const Ray3D& ray, float t_min, float t_max, HitResult& result){
        Vector3 oc = ray.Origin() - m_Center; 

        float a = ray.Direction().LengthSquared(); 
        float half_b = Vector3::Dot(oc, ray.Direction());
        float c = oc.LengthSquared() - (m_Radius * m_Radius);

        float discriminant = (half_b * half_b) - a * c;

        if(discriminant < 0){
            return false;
        }

        float rootd = sqrt(discriminant); 

        float root = (-half_b - rootd) / a;
        if(root <= t_min || t_max <= root){
            root = (-half_b + rootd) / a;
            if(root <= t_min || t_max <= root){
                return false;
            }
        }

        result.t = root; 
        result.Point = ray.At(root);
        result.Normal = (result.Point - m_Center) / m_Radius;

        return true;
    }
}

#endif
