#ifndef _FIREFLY_MATERIAL_METAL_H
#define _FIREFLY_MATERIAL_METAL_H

#include "../Material.h"

namespace Firefly
{
    class Metal : public IMaterial
    {
        public:
            Metal(Colour albedo = {}, float fuzziness = 1.0f);
            bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const override;

        private:
            Colour m_Albedo;
            float m_Fuzziness;
    };
        
    inline Metal::Metal(Colour albedo, float fuzziness)
    {
        m_Albedo = albedo;
    }

    inline bool Metal::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{
        Vector3 inNorm = inRay.Direction();
        inNorm = Vector3::Normalize(inNorm);
        Vector3 reflectDir = Vector3::Reflect(inNorm, result.Normal);

        scatter = Ray3D(result.Point, reflectDir + m_Fuzziness * Vector3::Random());
        attenuation = m_Albedo;
        return (Vector3::Dot(scatter.Direction(), result.Normal) > 0.0f);
    }


}
#endif
