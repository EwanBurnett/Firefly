#ifndef _FIREFLY_IMAGE_H
#define _FIREFLY_IMAGE_H

#include "ColourRGBA.h"
#include <vector> 
#include <string>

namespace Firefly
{
    class Image
    {
        public: 

            Image();
            Image(const uint32_t width, const uint32_t height, const std::string& name);
            ~Image();

            std::vector<ColourRGBA>& Pixels(); 
            uint32_t Width() const;
            uint32_t Height() const;

            const std::string& Name() const;
        private:
            std::vector<ColourRGBA> m_Pixels;
            std::string m_Name;
            uint32_t m_Width;
            uint32_t m_Height;
    };


    inline Image::Image()
    {

    }

    inline Image::Image(const uint32_t width, const uint32_t height, const std::string& name)
    {
        m_Width = width;
        m_Height = height;

        m_Pixels.resize(width * height);

        m_Name = name;
    }

    inline Image::~Image()
    {

    }

    inline std::vector<ColourRGBA>& Image::Pixels()
    {
        return m_Pixels;
    }
     
    inline uint32_t Image::Height() const{
        return m_Height;
    }

    inline uint32_t Image::Width() const{
        return m_Width;
    }
    
    inline const std::string& Image::Name() const{
        return m_Name;
    }
}

#endif
