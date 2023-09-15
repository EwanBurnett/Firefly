#ifndef _FIREFLY_WORLD_H
#define _FIREFLY_WORLD_H

#include "Object.h"

#include <string>
#include <vector>

namespace Firefly
{
    class Camera;
    class Viewport; 

    class World
    {
        public:
            World();
            ~World();

            void LoadFromFile(const std::string& filePath, const Viewport& viewport);
            const std::vector<IObject*>& GetScene() const; 

            const std::vector<Camera>& GetCameras() const;

        private:
            IObject* ObjectFactory(const std::string& type, void* pElement);
            std::shared_ptr<IMaterial> MaterialFactory(const std::string& type, void* pElement);
            std::vector<IObject*> m_Objects;
            std::vector<Camera> m_Cameras;
    };
}

#endif
