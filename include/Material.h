#ifndef _FIREFLY_MATERIAL_H
#define _FIREFLY_MATERIAL_H

#include "Ray3D.h"
#include "ColourRGBA.h"
#include "HitResult.h"

namespace Firefly
{
    class IMaterial
    {
        public:
            virtual ~IMaterial();

            virtual bool Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const;
    };


    inline IMaterial::~IMaterial(){

    }

        
    inline bool IMaterial::Scatter(Ray3D inRay, HitResult& result, Colour& attenuation, Ray3D& scatter) const{
        return false;
    }
}


#endif
