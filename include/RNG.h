#ifndef _FIREFLY_RNG_H
#define _FIREFLY_RNG_H

#include <random>

namespace Firefly
{
    class RNG{
        public:
            RNG(); 
            float RandomFloat(const float min, const float max);
        private:
            std::mt19937 m_rng;
            std::random_device m_device;
    };

    inline RNG::RNG(){
        m_rng = std::mt19937(m_device());
    }

    inline float RNG::RandomFloat(const float min, const float max)
    {
         std::uniform_real_distribution<> dist(min, max);
         return dist(m_rng);
    }

}
#endif
