#ifndef _FIREFLY_MATERIAL_GLASS_H
#define _FIREFLY_MATERIAL_GLASS_H

#include "../Material.h"

namespace Firefly
{
    class Glass : public IMaterial
    {
        public:
            Glass(Colour albedo = {});
            bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const override;

        private:
            Colour m_Albedo;
    };
        
    inline Glass::Glass(Colour albedo)
    {
        m_Albedo = albedo;
    }

    inline bool Glass::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{
        Vector3 randDir = Vector3::Random(); 
        Vector3 scatterDir = result.Normal + Vector3::Normalize(randDir);
        scatter = Ray3D(result.Point, scatterDir);
        attenuation = m_Albedo;
        return true;
    }


}
#endif
