#include <cstdio>
#include <stb_image.h>
#include <thread>
#include "../include/Progressbar.h"
#include "../include/RNG.h"
#include "../include/Exporter.h"
#include "../include/Timer.h"

//USAGE
//Firefly:
//    -w : Width - target image width
//    -h : Height - target image height

int main(int argc, char** argv)
{
    printf("Firefly v%d.%da\n", FIREFLY_VERSION_MAJOR, FIREFLY_VERSION_MINOR);
    
    uint16_t width = 0;
    uint16_t height = 0;
    char* fileName = __TIME__;


    //Parse CMD arguments
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-w") == 0){
                width = std::atoi(argv[i + 1]);
            }

            else if(strcmp(argv[i], "-h") == 0){
                height = std::atoi(argv[i + 1]);
            }

            else if(strcmp(argv[i], "-f") == 0){
                fileName = argv[i + 1];
            }
        }        
    }
    
    if(width == 0){
        throw std::runtime_error("Width was 0!\n");
    }
    if(height == 0){
        throw std::runtime_error("Height was 0!\n");
    }

    uint32_t numPixels = (uint32_t)(width * height);
    printf("Rendering an Image [%dx%d] (%d pixels)\n", width, height, numPixels);

    std::vector<Firefly::ColourRGBA> img(width * height);

    Firefly::Timer timer;
    timer.Start();
    Firefly::ProgressBar pb(height, "Rendering Image...", 40);

    //Render the Image
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            Firefly::ColourRGBA* pColour = &img[(width * y) + x];
            pColour->r = (uint8_t)(((float)y / (float)height) * 255.0f);
            pColour->g = 64;
            pColour->b = (uint8_t)(((float)x / (float)width) * 255.0f);
            pColour->a = 255;
        }

        pb.Advance();     
        timer.Tick();
    }

    printf("\nImage Rendered in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);

    Firefly::Exporter::ExportToPPM(fileName, width, height, img);
    Firefly::Exporter::ExportToPNG(fileName, width, height, img);
}
