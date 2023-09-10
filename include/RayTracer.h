#ifndef _FIREFLY_RAYTRACER_H
#define _FIREFLY_RAYTRACER_H

#include <cmath>
#include "Vector3.h"
#include "ColourRGBA.h"
#include "Ray3D.h"
#include "Image.h"
#include "Camera.h"
#include "World.h"
#include <cstdio>
#include "Progressbar.h"
#include "Timer.h"

namespace Firefly{

    class RayTracer{

        public:
            RayTracer();
            ~RayTracer();

            void Render(const World& world, const Camera& camera, Image& outputImage);

        private:
            ColourRGBA RayColour(const Ray3D& ray, const World& world);
    };


    inline RayTracer::RayTracer(){

    }

    inline RayTracer::~RayTracer(){

    }

    inline void RayTracer::Render(const World& world, const Camera& camera, Image& outputImage){

        const uint32_t width = outputImage.Width();
        const uint32_t height = outputImage.Height();


        char buffer[256];
        sprintf(buffer, "Rending Image %s [%dx%d]\n", outputImage.Name().c_str(), width, height);
        
        //Calculate the delta vectors for each pixel
        Viewport viewport = camera.GetViewport(); 
        Vector3 pixelDeltaU = viewport.ViewportU() / (float)width;
        Vector3 pixelDeltaV = viewport.ViewportV() / (float)height;
        
        //Calculate where the upper-left-most pixel is
        Vector3 originPixel = viewport.TopLeft(camera.GetPosition(), camera.GetFocalLength()) + (0.5f * (pixelDeltaU + pixelDeltaV)); 

 
        Firefly::Timer timer;
        timer.Start();
        Firefly::ProgressBar progressBar(height, buffer, 40);

        //Render the Image
        for(int y = 0; y < height; y++){
            //Process each Scanline
            for(int x = 0; x < width; x++){
                Vector3 pixelCenter = originPixel + (pixelDeltaU * x) + (pixelDeltaV * y);
                Vector3 rayDir = pixelCenter - camera.GetPosition(); 
                rayDir = Vector3::Normalize(rayDir);
                Ray3D ray(camera.GetPosition(), rayDir);

                ColourRGBA* pColour = &(outputImage.Pixels()[(width * y) + x]);
            
                auto rayColour = RayColour(ray, world);
                *pColour = rayColour; 
        }

        progressBar.Advance();     
        timer.Tick();
    }

    printf("\nImage %s Rendered in %fs!\n", outputImage.Name().c_str(), timer.Get<std::chrono::milliseconds>() / 1000.0f);

    }

    inline ColourRGBA RayTracer::RayColour(const Ray3D& ray, const World& world){
        for(auto& obj : world.GetScene()){
            float t = (obj->Hit(ray));
            if(t > 0.0f){
                Vector3 v = (ray.At(t) - Vector3(0.0f, 0.0f, -1.0f));
                Vector3 N = Vector3::Normalize(v);
                ColourRGBA c = {
                    (uint8_t)(255.99f * (0.5f * (N.x + 1))),
                    (uint8_t)(255.99f * (0.5f * (N.y + 1))),
                    (uint8_t)(255.99f * (0.5f * (N.z + 1))),
                    255
                };
                return c;
            }
        }
        Vector3 dir = ray.Direction();
        auto k = 0.5f * (dir.y + 1.0f);
        auto a = ColourRGBA{0x9e, 0x33, 0x4a, 180};
        auto b = ColourRGBA{0x0d, 0x56, 0x9e, 255};

        return{
            (uint8_t)(((1.0f - k) * a.r + k * b.r)),
            (uint8_t)(((1.0f - k) * a.g + k * b.g)),
            (uint8_t)(((1.0f - k) * a.b + k * b.b)),
            (uint8_t)(((1.0f - k) * a.a + k * b.a)),
        };
    }
}
#endif
