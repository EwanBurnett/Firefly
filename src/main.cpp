#include <cstdio>
#include <stb_image.h>
#include <thread>
#include "../include/Progressbar.h"
#include "../include/RNG.h"
#include "../include/Exporter.h"
#include "../include/Timer.h"
#include "../include/Viewport.h"
#include "../include/Camera.h"
#include "../include/Ray3D.h"
#include "../include/Image.h"
#include "../include/RayTracer.h"
#include "../include/World.h"

//USAGE
//Firefly:
//    -w : Width - target image width
//    -h : Height - target image height

int main(int argc, char** argv)
{
    printf("Firefly v%d.%da\n", FIREFLY_VERSION_MAJOR, FIREFLY_VERSION_MINOR);
    

    uint16_t width = 100;
    uint16_t height = 100;

    uint32_t numSamples = 1;
    uint32_t depth = 1;

    char* fileName = __TIME__;
    char* sceneFile = "";

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

            else if(strcmp(argv[i], "-s") == 0){
                sceneFile = argv[i + 1];
            }

            else if(strcmp(argv[i], "-a") == 0){
                numSamples = atoi(argv[i + 1]);
            }
            
            else if(strcmp(argv[i], "-d") == 0){
                depth = atoi(argv[i + 1]);
            }
        }        
    }
    
    //Validate input arguments
    {
        if(width == 0){
            throw std::runtime_error("Width was 0!\nImage Width must be greater than 0.\n");
        }
        if(height == 0){
            throw std::runtime_error("Height was 0!\nImage Height must be Greater than 0.\n");
        }

        if(strcmp(sceneFile, "") == 0){
            throw std::runtime_error("No Scene was Loaded!\nPlease Specify a Scene File with the -s [filepath] flag.\n");
        }

        if(numSamples < 1){
            numSamples = 1;
        }

        if(depth < 1){
            depth = 1;
        }
    }


    Firefly::Viewport vp(width, height);
    Firefly::World world;
    world.LoadFromFile(sceneFile, vp);

    Firefly::Camera camera;
    {
        auto cameras = world.GetCameras();
        if(cameras.empty()){
            camera = {{0.0f, 0.0f, 0.0f}, vp};
        }
        else{
            camera = cameras[0]; //Use the Default camera from the World.
        }
    }
    Firefly::Image img(width, height, fileName);
    Firefly::RayTracer rt(numSamples, depth);
    rt.Render(world, camera, img);

    //Firefly::Exporter::ExportToPPM(fileName, width, height, img.Pixels());
    Firefly::Exporter::ExportToPNG(fileName, width, height, img.Pixels());
}
