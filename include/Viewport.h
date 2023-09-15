#ifndef _FIREFLY_VIEWPORT_H
#define _FIREFLY_VIEWPORT_H

#include "../include/Vector3.h"
#include <cstdint>

namespace Firefly
{
    class Viewport
    {
        public:
            friend class Camera;
            Viewport();
            Viewport(const uint16_t width, const uint16_t height);

            uint32_t Width() const;
            uint32_t Height() const;

            Vector3 ViewportU() const;
            Vector3 ViewportV() const;

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

    inline uint32_t Viewport::Width() const{
        return m_ViewportWidth;
    }

    inline uint32_t Viewport::Height() const{
        return m_ViewportHeight;
    }

    inline Vector3 Viewport::ViewportU() const{
        return {m_ViewportWidth, 0.0f, 0.0f};
    }
    
    inline Vector3 Viewport::ViewportV() const{
        return {0.0f, -m_ViewportHeight, 0.0f};
    }

}
#endif
