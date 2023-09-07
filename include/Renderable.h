#ifndef _FIREFLY_RENDERABLE_H
#define _FIREFLY_RENDERABLE_H

#include "Ray3D.h"
#include "Object.h"
#include "HitResult.h"

namespace Firefly
{
    class IRenderable : public IObject
    {
        public:
            virtual bool IsHit(const Ray3D& ray, float t_min, float t_max, HitResult&  result) const;
    };
}

#endif
