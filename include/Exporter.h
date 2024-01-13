#ifndef _FIREFLY_EXPORTER_H
#define _FIREFLY_EXPORTER_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include <future>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "../include/ColourRGBA.h"
#include "../include/Timer.h"
#include "../include/Progressbar.h"

namespace Firefly
{
    class Exporter
    {
        public:
            static void ExportToPPM(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image);

            static void ExportToPNG(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image);
    };
    
    inline void Exporter::ExportToPPM(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image){

        char name[256];
        strcpy(name, fileName);
        strcat(name, ".ppm");

        printf("Exporting image %s [%dx%d] to PPM\n", name, width, height);
        Timer timer;
        timer.Start(); 

        std::future<void> writeToFile = std::async(std::launch::deferred, [&]{
                   FILE* outputImage; 
            outputImage = fopen(name, "w");
            if(outputImage == nullptr){
                throw std::runtime_error("Unable to create Output File!\n");
                return;
            }
            else{
                //Write the PPM Header
                fprintf(outputImage, "P3\n%d %d\n255\n", width, height);

                //Write the Image Data
                const uint32_t size = image.size();

                ProgressBar progressbar(height, "Exporting Image to PPM", 40);

                for(uint32_t i = 0; i < size; i++){

                    const uint32_t r = image[i].r;
                    const uint32_t g = image[i].g;
                    const uint32_t b = image[i].b;
                    const uint32_t a = image[i].a;

                    fprintf(outputImage, "%d %d %d\n", r, g, b);
                    
                    if((i % width) == 0){
                        progressbar.Advance(); 
                    }

                }
               fclose(outputImage);
                
            }
            
        });

        writeToFile.wait(); 
        printf("\nExport Complete in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);
    }

    inline void Exporter::ExportToPNG(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image){

        char name[256];
        strcpy(name, fileName);
        strcat(name, ".png");
        printf("Exporting image %s [%dx%d] to PNG\n", fileName, width, height);
        
        Timer timer;
        timer.Start();

        stbi_write_png(name, width, height, 4, image.data(), width * 4);

        timer.Tick();
        printf("Export Complete in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);
        
           

    }
}
#endif
