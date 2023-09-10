#ifndef _FIREFLY_INTERVAL_H
#define _FIREFLY_INTERVAL_H

#include "MathHelper.h"

namespace Firefly
{
    struct Interval
    {
        public:
            Interval();
            Interval(float min, float max);

            bool Contains(float x) const;
            bool Surrounds(float x) const;

            float Clamp(float x) const;

            const static Interval Empty();
            const static Interval Universe(); 

        public:
            float m_Min;
            float m_Max; 

    };

    inline Interval::Interval(){
        m_Min = +Infinity;
        m_Max = -Infinity;
    }

    inline Interval::Interval(float min, float max){
        m_Min = min;
        m_Max = max; 
    }

    inline bool Interval::Contains(float x) const {
        return m_Min <= x && x <= m_Max;
    }

    inline bool Interval::Surrounds(float x) const {
        return m_Min < x && x < m_Max;
    }

    inline const Interval Interval::Empty(){
        return {+Infinity, -Infinity};
    }
    
    inline const Interval Interval::Universe(){
        return {-Infinity, +Infinity};
    }

    inline float Interval::Clamp(float x) const{
        if(x < m_Min){
            return m_Min;
        }
        else if(x > m_Max){
            return m_Max;
        }

        return x; 
    }

}

#endif
