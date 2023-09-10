#ifndef _FIREFLY_OBJECT_H
#define _FIREFLY_OBJECT_H

#include "Vector3.h"
#include "Ray3D.h"

namespace Firefly
{
    class IObject
    {
        public:
            IObject(); 
            virtual ~IObject(); 

            virtual float Hit(const Ray3D& ray)
            {
                return 0.0f;
            }

    };

    inline IObject::IObject(){

    }

    inline IObject::~IObject(){

    }
}

#endif
