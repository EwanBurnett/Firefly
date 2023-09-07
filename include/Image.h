#ifndef _FIREFLY_IMAGE_H
#define _FIREFLY_IMAGE_H

#include "ColourRGBA.h"
#include <vector>

namespace Firefly
{
    class Image
    {
        public: 
            Image();
            Image(const uint32_t width, const uint32_t height);
            ~Image();

            const std::vector<ColourRGBA>& Pixels();

            uint32_t Height() const;
            uint32_t Width() const;

        private:
            uint32_t m_Width;
            uint32_t m_Height;
            std::vector<ColourRGBA> m_Pixels;
    };
}

inline Firefly::Image::Image()
{

}

inline Firefly::Image::Image(const uint32_t width, const uint32_t height)
{
    m_Width = width;
    m_Height = height;

    m_Pixels.resize(width * height);
}

inline Firefly::Image::~Image()
{

}

inline const std::vector<Firefly::ColourRGBA>& Firefly::Image::Pixels()
{
    return m_Pixels;
}

inline uint32_t Firefly::Image::Height() const
{
    return m_Height;
}

inline uint32_t Firefly::Image::Width() const
{
    return m_Width;
}



#endif
