#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include <cmath>
#include "Vector3.h"
#include "ColourRGBA.h"
#include "Camera.h"
#include "Ray3D.h"
#include "Interval.h"
#include "Image.h"
#include "RNG.h"
#include "World.h"
#include <cstdio>
#include "Progressbar.h"
#include "Timer.h"

namespace Firefly{

    class RayTracer{

        public:
            RayTracer(uint32_t samples = 1);
            ~RayTracer();
            
            void Render(const World& world, const Camera& camera, Image& outputImage);

        private:
            Colour RayColour(const Ray3D& ray, const World& world);
            Ray3D GetRandomRay(const Vector3& center, uint32_t x, uint32_t y, const Vector3& pixelOrigin, const Vector3& pixelDeltaU, const Vector3& pixelDeltaV);
            Vector3 PixelSampleSquare(const Vector3& pixelDeltaU, const Vector3& pixelDeltaV);

            RNG m_RNG;
            uint32_t m_Samples; 
    };


    inline RayTracer::RayTracer(uint32_t samples){
        m_Samples = samples;
    }

    inline RayTracer::~RayTracer(){

    }

    inline void RayTracer::Render(const World& world, const Camera& camera, Image& outputImage){

        const uint32_t width = outputImage.Width();
        const uint32_t height = outputImage.Height();


        char buffer[256];
        sprintf(buffer, "Rending Image %s [%dx%d]\t", outputImage.Name().c_str(), width, height);
        
        //Calculate the delta vectors for each pixel
        Viewport viewport = camera.GetViewport(); 
        
        //Calculate where the upper-left-most pixel is
        Firefly::Timer timer;
        timer.Start();
        Firefly::ProgressBar progressBar(height, buffer, 40);

        //Render the Image
        for(int y = 0; y < height; y++){
            //Process each Scanline
            for(int x = 0; x < width; x++){
                
                ColourRGBA* pColour = &(outputImage.Pixels()[(width * y) + x]);
                
                float scale = 1.0f / m_Samples;
                Colour colour = {}; 

                auto pixelOrigin = camera.PixelOrigin(width, height);
                auto pixelDeltaU = camera.PixelDeltaU(width);
                auto pixelDeltaV = camera.PixelDeltaV(height);

                for(uint32_t i = 0; i < m_Samples; i++){
                    Ray3D ray = GetRandomRay(camera.GetPosition(), x, y, pixelOrigin, pixelDeltaU, pixelDeltaV);
                    Colour rayColour = RayColour(ray, world);

                    colour.r += rayColour.r;
                    colour.g += rayColour.g;
                    colour.b += rayColour.b;
                    colour.a += rayColour.a;
                }

                colour.r /= scale;
                colour.g /= scale;
                colour.b /= scale;
                colour.a /= scale;
                
                Interval iv(0.0f, 0.999f);
                *pColour = ColourRGBA(
                    (uint8_t)(255.99f * iv.Clamp(colour.r)),
                    (uint8_t)(255.99f * iv.Clamp(colour.g)),
                    (uint8_t)(255.99f * iv.Clamp(colour.b)),
                    (uint8_t)(255.99f * iv.Clamp(colour.a))
                    ); 
        }

        progressBar.Advance();     
        timer.Tick();
    }

    printf("\nImage %s Rendered in %fs!\n", outputImage.Name().c_str(), timer.Get<std::chrono::milliseconds>() / 1000.0f);

    }

    inline Colour RayTracer::RayColour(const Ray3D& ray, const World& world){
        for(auto& obj : world.GetScene()){
            float t = (obj->Hit(ray));
            if(t > 0.0f){
                Vector3 v = (ray.At(t) - Vector3(0.0f, 0.0f, -1.0f));
                Vector3 N = Vector3::Normalize(v);
                Colour c = {
                    (0.5f * (N.x + 1.0f)),
                    (0.5f * (N.y + 1.0f)),
                    (0.5f * (N.z + 1.0f)),
                    1.0f
                };
                return c;
            }
        }
        
        Vector3 dir = ray.Direction();
        auto k = 0.5f * (dir.y + 1.0f);
        Colour a = Colour(ColourRGBA{0x9e, 0x33, 0x4a, 180});
        Colour b = Colour(ColourRGBA{0x0d, 0x56, 0x9e, 255});

        return{
            ((1.0f - k) * a.r + k * b.r),
            ((1.0f - k) * a.g + k * b.g),
            ((1.0f - k) * a.b + k * b.b),
            ((1.0f - k) * a.a + k * b.a),
        };
    }

    inline Ray3D RayTracer::GetRandomRay(const Vector3& center, uint32_t x, uint32_t y, const Vector3& pixelOrigin, const Vector3& pixelDeltaU, const Vector3& pixelDeltaV){
        Vector3 pixelCenter = pixelOrigin + (pixelDeltaU * x) + (pixelDeltaV * y);
        Vector3 pixelSample = pixelCenter + PixelSampleSquare(pixelDeltaU, pixelDeltaV);

        Vector3 rayOrigin = center; 
        Vector3 rayDir = pixelSample - rayOrigin;
        rayDir = Vector3::Normalize(rayDir);

        return Ray3D(rayOrigin, rayDir);
    }

    inline Vector3 RayTracer::PixelSampleSquare(const Vector3& pixelDeltaU, const Vector3& pixelDeltaV){

        float squareX = -0.5f + m_RNG.RandomFloat();
        float squareY = -0.5f + m_RNG.RandomFloat();

        return (squareX * pixelDeltaU) + (squareY * pixelDeltaV);
    }
}
#endif
