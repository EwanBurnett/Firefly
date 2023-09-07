#ifndef _FIREFLY_HIT_RESULT_H
#define _FIREFLY_HIT_RESULT_H

#include "Vector3.h"

namespace Firefly
{
    struct HitResult
    {
        Vector3 Point; 
        Vector3 Normal;
        float t;
    };

}
#endif
