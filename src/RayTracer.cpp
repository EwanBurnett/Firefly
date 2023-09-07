#include "../include/RayTracer.h"
#include "../include/Exporter.h"


Firefly::RayTracer::RayTracer(){
    //Initialize the Ray Tracer
    Firefly::Viewport viewport(width, height);
    Firefly::Camera camera({0.0f, 0.0f, 0.0f}, viewport);

    //Calculate the delta vectors for each pixel
    Firefly::Vector3 pixelDeltaU = viewport.ViewportU() / (float)width;
    Firefly::Vector3 pixelDeltaV = viewport.ViewportV() / (float)height;
    
    //Calculate where the upper-left-most pixel is
    Firefly::Vector3 originPixel = viewport.TopLeft(camera.GetPosition(), camera.GetFocalLength()) + (0.5f * (pixelDeltaU + pixelDeltaV)); 


}

Firefly::RayTracer::~RayTracer()
{
    //Wait for all exports to finish before exiting
    for(std::future<void> export : m_Exports){
        export.wait();
    }
}

void Firefly::RayTracer::Render(const World& world)
{
       
    //Create the output Image


    //Start the timer / progress bar
    Firefly::Timer timer;
    timer.Start();
    Firefly::ProgressBar pb(height, "Rendering Image...", 40);

    //Render the Image
    for(int y = 0; y < image.Height(); y++)
    {
        //Process this scanline
        ScanLine(y, image);

        progressBar.Advance();
        timer.Tick();

    }

    printf("\nImage Rendered in %fs!\n", timer.Get<std::chrono::milliseconds>() / 1000.0f);

}

void Firefly::RayTracer::Update(World& world, const float deltaTime)
{

}

void Firefly::RayTracer::ScanLine(size_t lineIdx, std::vector<char>& outImage)
{
    const uint32_t y = lineIdx;
    
    for(uint32_t x = 0; x < outImage.Width(); x++){
        Firefly::Vector3 pixelCenter = originPixel + (pixelDeltaU * x) + (pixelDeltaV * y);
        Firefly::Vector3 rayDir = pixelCenter - camera.GetPosition(); 
        rayDir = Firefly::Vector3::Normalize(rayDir);
        Firefly::Ray3D ray(camera.GetPosition(), rayDir);

        Firefly::ColourRGBA* pColour = &img[(width * y) + x];
        
        auto rayColour = Firefly::RayColour(ray);
        *pColour = rayColour; 
    }
}

Firefly::ColourRGBA RayColour(const Ray3D& ray, const World& world)
{

}   

bool RayCastHit(const Ray3D& ray, HitResult& result, const World& world)
{

} 
