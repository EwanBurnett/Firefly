#ifndef _FIREFLY_VIEWPORT_H
#define _FIREFLY_VIEWPORT_H

namespace Firefly
{
    class Viewport
    {
        public:
            Viewport();
            Viewport(const uint16_t width, const uint16_t height);


        private:
            float m_AspectRatio;
            uint16_t m_ViewportWidth;
            uint16_t m_ViewportHeight;

    };

    inline Viewport::Viewport(){

    }

    inline Viewport::Viewport(const uint16_t width, const uint16_t height){
        m_AspectRatio = (float)width / (float)height; 

        m_ViewportHeight = 2.0f; //TODO: Replace arbitrary height
        m_ViewportWidth = m_ViewportHeight * m_AspectRatio;
    }
}
#endif
