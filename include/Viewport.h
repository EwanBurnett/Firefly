#ifndef _FIREFLY_VIEWPORT_H
#define _FIREFLY_VIEWPORT_H

#include "../include/Vector3.h"


namespace Firefly
{
    class Viewport
    {
        public:
            Viewport();
            Viewport(const uint16_t width, const uint16_t height);

            Vector3 ViewportU() const;
            Vector3 ViewportV() const;

            Vector3 TopLeft(const Vector3& origin, const float FocalLength) const;

        private:
            float m_AspectRatio;
            float  m_ViewportWidth;
            float  m_ViewportHeight;

    };

    inline Viewport::Viewport(){

    }

    inline Viewport::Viewport(const uint16_t width, const uint16_t height){
        m_AspectRatio = (float)width / (float)height; 

        m_ViewportHeight = 2.0f; //TODO: Replace arbitrary height
        m_ViewportWidth = m_ViewportHeight * (static_cast<double>(width) / (float)height);
    }

    inline Vector3 Viewport::ViewportU() const{
        return {m_ViewportWidth, 0.0f, 0.0f};
    }
    
    inline Vector3 Viewport::ViewportV() const{
        return {0.0f, -m_ViewportHeight, 0.0f};
    }

    inline Vector3 Viewport::TopLeft(const Vector3& origin, const float FocalLength)const{
        Vector3 o = origin;
        return o - Vector3{0.0f, 0.0f, FocalLength} - (ViewportU() / 2.0f) - (ViewportV() / 2.0f);
    }
}
#endif
