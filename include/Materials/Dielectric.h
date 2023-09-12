#ifndef _FIREFLY_MATERIAL_DIELECTRIC_H
#define _FIREFLY_MATERIAL_DIELECTRIC_H

#include "../Material.h"
#include "../RNG.h"

namespace Firefly
{
    class Dielectric : public IMaterial
    {
        public:
            Dielectric(Colour tint = {}, float indexOfRefraction = 1.0f);
            bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const override;

        private:

            float Reflectance(float cosine, float refIdx) const;

            Colour m_Tint;
            float m_IR; 
    };
        
    inline Dielectric::Dielectric(Colour tint, float indexOfRefraction)
    {
        m_Tint = tint;
        m_IR = indexOfRefraction;
    }

    inline bool Dielectric::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{

        float ratioOfRefraction = result.isFrontFacing ? (1.0f / m_IR) : m_IR; 

        Vector3 inDir = inRay.Direction();
        Vector3 unitDir = Vector3::Normalize(inDir);
        
        float cosTheta = fminf(Vector3::Dot(-unitDir, result.Normal), 1.0f);
        float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);
        
        bool cannot_refract = ratioOfRefraction * sinTheta > 1.0f;
        Vector3 direction = {};

        static RNG rng;
        if(cannot_refract || Reflectance(cosTheta, ratioOfRefraction) > rng.RandomFloat()){
            direction = Vector3::Reflect(unitDir, result.Normal);
        }
        else{
            direction = Vector3::Refract(unitDir, result.Normal, ratioOfRefraction);
        }
        scatter = Ray3D(result.Point, direction);
        attenuation = m_Tint;

        return true;
    }


    inline float Dielectric::Reflectance(float cosine, float refIdx) const
    {
        //Schlick's approximation
        float r0 = (1.0f - refIdx) / (1.0f + refIdx);
        r0 = r0 * r0;
        return r0 + (1.0f + r0) * pow((1.0f - cosine), 5);
    }
}
#endif
