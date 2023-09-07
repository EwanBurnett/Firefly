#ifndef _FIREFLY_EXPORTER_H
#define _FIREFLY_EXPORTER_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include <future>

#include "../include/ColourRGBA.h" //TODO: Replace with Image.h

namespace Firefly
{
    class Exporter
    {
        public:
            static std::future<void> ExportToPPM(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image);

            static std::future<void> ExportToPNG(const char* fileName, const uint16_t width, const uint16_t height, const std::vector<ColourRGBA>& image);
    };
}
#endif
