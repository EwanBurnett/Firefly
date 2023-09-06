#ifndef _FIREFLY_RAY3D_H
#define _FIREFLY_RAY3D_H

#include "../include/Vector3.h"

namespace Firefly{
    class Ray3D{
        public:
            Ray3D(); 
            Ray3D(const Vector3& origin, const Vector3& direction);

            Vector3 At(float t) const;

            Vector3 Origin() const;
            Vector3 Direction() const;

        private:
            Vector3 m_Origin;
            Vector3 m_Direction; 
    };

    inline Ray3D::Ray3D(){
        m_Origin = {};
        m_Direction = {};
    }

    inline Ray3D::Ray3D(const Vector3& origin, const Vector3& direction){
        m_Origin = origin;
        m_Direction = direction;
    }

    inline Vector3 Ray3D::At(float t) const {
        Vector3 v = m_Origin + (m_Direction * t);
        return v;
    }
    
    inline Vector3 Ray3D::Origin() const{
        return m_Origin;
    }

    inline Vector3 Ray3D::Direction() const{
        return m_Direction;
    }
}
#endif
