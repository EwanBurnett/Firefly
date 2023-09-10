#ifndef _FIREFLY_RNG_H
#define _FIREFLY_RNG_H

#include <random>

namespace Firefly
{
    class RNG{
        public:
            RNG(); 
            float RandomFloat(); 
            float RandomFloat(const float min, const float max);
        private:
            std::mt19937 m_rng;
            std::random_device m_device;
    };

    inline RNG::RNG(){
        m_rng = std::mt19937(m_device());
    }

    inline float RNG::RandomFloat(){
        static std::uniform_real_distribution<float> dist_0_1(0.0f, 1.0f);
        return dist_0_1(m_rng);
    }

    inline float RNG::RandomFloat(const float min, const float max)
    {
         std::uniform_real_distribution<> dist(min, max);
         return dist(m_rng);
    }

}
#endif
