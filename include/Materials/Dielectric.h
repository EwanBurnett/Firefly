#ifndef _FIREFLY_MATERIAL_DIELECTRIC_H
#define _FIREFLY_MATERIAL_DIELECTRIC_H

#include "../Material.h"
#include "../RNG.h"

namespace Firefly
{
    class Dielectric : public IMaterial
    {
        public:
            Dielectric(Colour tint = {}, float indexOfRefraction = 1.0f, float fresnel = 1.0f);
            bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const override;

        private:

            float Reflectance(float cosine, float refIdx) const;
            float Fresnel(const Vector3& vector, const Vector3& normal) const;

            Colour m_Tint;
            float m_IR; 
            float m_Fresnel; 
    };
        
    inline Dielectric::Dielectric(Colour tint, float indexOfRefraction, float fresnel)
    {
        m_Tint = tint;
        m_IR = indexOfRefraction;
        m_Fresnel = fresnel;
    }

    inline bool Dielectric::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{

        float ratioOfRefraction = result.isFrontFacing ? (1.0f / m_IR) : m_IR; 

        Vector3 inDir = inRay.Direction();
        Vector3 unitDir = Vector3::Normalize(inDir);
        
        float cosTheta = fminf(Vector3::Dot(-unitDir, result.Normal), 1.0f);
        float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);
        
        bool cannot_refract = ratioOfRefraction * sinTheta > 1.0f;

        static RNG rng;
        bool shouldReflect = Reflectance(cosTheta, ratioOfRefraction) > rng.RandomFloat();
        Vector3 direction = {};

        if(cannot_refract || shouldReflect){
            direction = Vector3::Reflect(unitDir, result.Normal);
        }
        else{
            direction = Vector3::Refract(unitDir, result.Normal, ratioOfRefraction);
        }
        scatter = Ray3D(result.Point, direction);
            
        float f = Fresnel(inRay.Direction(), result.Normal) * m_Fresnel;

        attenuation.r = (1.0f - f) * m_Tint.r;
        attenuation.g = (1.0f - f) * m_Tint.g;
        attenuation.b = (1.0f - f) * m_Tint.b;
        attenuation.a = (1.0f - f) * m_Tint.a;

        return true;
    }


    inline float Dielectric::Reflectance(float cosine, float refIdx) const
    {
        //Schlick's approximation
        float r0 = (1.0f - refIdx) / (1.0f + refIdx);
        r0 = r0 * r0;
        return r0 + (1.0f + r0) * pow((1.0f - cosine), 5);
    }

    inline float Dielectric::Fresnel(const Vector3& vector, const Vector3& normal) const
    {
        return powf(1.0f + Vector3::Dot(vector, normal), 3.0f); //The Fresnel Effect 
    }
}
#endif
