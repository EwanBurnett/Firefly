#ifndef _FIREFLY_MATERIAL_LAMBERT_H
#define _FIREFLY_MATERIAL_LAMBERT_H

#include "../Material.h"

namespace Firefly
{
    class Lambert : public IMaterial
    {
        public:
            Lambert(Colour albedo = {});
            bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const override;

        private:
            Colour m_Albedo;
    };
        
    inline Lambert::Lambert(Colour albedo)
    {
        m_Albedo = albedo;
    }

    inline bool Lambert::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{
        Vector3 randDir = Vector3::Random(); 
        Vector3 scatterDir = result.Normal + Vector3::Normalize(randDir);

        //Catch Degenerate Scatter Direction
        if(Vector3::NearlyEqual(scatterDir, {0.0f, 0.0f, 0.0f})){
            scatterDir = result.Normal;
        }

        scatter = Ray3D(result.Point, scatterDir);
        attenuation = m_Albedo;
        return true;
    }


}
#endif
