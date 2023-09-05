#include <cstdio>
#include <stb_image.h>
#include <thread>
#include "../include/Progressbar.h"
#include "../include/RNG.h"
#include "../include/Exporter.h"
#include "../include/Timer.h"

int main(int argc, const char** argv)
{
    printf("Firefly v%d.%da\n", FIREFLY_VERSION_MAJOR, FIREFLY_VERSION_MINOR);
    
    //Parse CMD arguments

    Firefly::Timer timer;
    timer.Start();
    Firefly::ProgressBar pb(100, "Rendering Image...", 40);
    for(int i = 0; i < 100; i++){
        pb.Advance();     
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        timer.Tick();
    }
    printf("\nImage Rendered in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);

    std::vector<Firefly::ColourRGBA> img = {
        {100, 200, 15, 2}, 
        {24, 95, 120, 15},
        {39, 77, 210, 0},
        {100, 100, 100, 200},
        {25, 25, 25, 100},
        {200, 200, 200, 100},
    };
    Firefly::Exporter::ExportToPPM("test.ppm", 3, 2, img);
}
