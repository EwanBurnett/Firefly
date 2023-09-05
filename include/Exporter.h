#ifndef _FIREFLY_EXPORTER_H
#define _FIREFLY_EXPORTER_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include <future>

#include "../include/ColourRGBA.h"
#include "../include/Timer.h"
#include "../include/Progressbar.h"

namespace Firefly
{
    class Exporter
    {
        public:
            static void ExportToPPM(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image);

    };
    
    inline void Exporter::ExportToPPM(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image){

        printf("Exporting image %s [%dx%d] to PPM\n", fileName, width, height);
        
        std::future<void> writeToFile = std::async(std::launch::deferred, [&]{
            Timer timer;
            timer.Start(); 
    
            FILE* outputImage; 
            outputImage = fopen(fileName, "w");
            if(outputImage == nullptr){
                throw std::runtime_error("Unable to create Output File!\n");
                return;
            }
            else{
                //Write the PPM Header
                fprintf(outputImage, "P3\n%d %d\n255\n", width, height);

                //Write the Image Data
                const uint32_t size = image.size();

                ProgressBar progressbar(size, "Exporting Image to PPM", 45);

                for(uint32_t i = 0; i < size; i++){

                    const uint32_t r = image[i].r;
                    const uint32_t g = image[i].g;
                    const uint32_t b = image[i].b;
                    const uint32_t a = image[i].a;

                    fprintf(outputImage, "%d %d %d", r, g, b);
                    
                    if((i % width) == 0){
                        fprintf(outputImage, "\n");
                    }

                    progressbar.Advance(); 
                }
                
            }
            
            printf("\nExport Complete in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);
        });

       writeToFile.wait(); 


}};

#endif
