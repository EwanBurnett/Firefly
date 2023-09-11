#ifndef _FIREFLY_OBJECT_H
#define _FIREFLY_OBJECT_H

#include "Vector3.h"
#include "Ray3D.h"
#include "HitResult.h"
#include "Interval.h"

namespace Firefly
{
    class IObject
    {
        public:
            IObject(); 
            virtual ~IObject(); 

            virtual bool Hit(const Ray3D& ray, Interval interval, HitResult& result)
            {
                return false;
            }

    };

    inline IObject::IObject(){

    }

    inline IObject::~IObject(){

    }
}

#endif
