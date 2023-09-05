#include <cstdio>
#include <stb_image.h>
#include <thread>
#include "../include/Progressbar.h"
#include "../include/RNG.h"

int main()
{
    printf("Firefly v%d.%da\n", FIREFLY_VERSION_MAJOR, FIREFLY_VERSION_MINOR);
    Firefly::RNG rng;
    float rand = rng.RandomFloat(0.0f, 100.0f);
    printf("\nRandom number: %f\n", rand);
    Firefly::ProgressBar pb(100, "Testing Progress Bar", 40);

    for(int i = 0; i < 100; i++){
        pb.Advance();     
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
