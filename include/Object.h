#ifndef _FIREFLY_OBJECT_H
#define _FIREFLY_OBJECT_H

#include "Vector3.h"

namespace Firefly
{
    class IObject
    {
        public:
            Vector3 position;
            float radius;
    };
}

#endif
