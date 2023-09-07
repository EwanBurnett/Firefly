#ifndef _FIREFLY_WORLD_H
#define _FIREFLY_WORLD_H

#include "Object.h"
#include "Renderable.h"
#include <vector> 
#include <string>

namespace Firefly{
    
    class World
    {
        public:
            friend class RayTracer;
            
            void LoadFromFile(const std::string& filePath);

        private:
            IObject* ConstructObject(const uint32_t type, const uint32_t id, const Vector3& position);

            std::vector<IObject*> m_Objects;
            std::vector<IRenderable*> m_Renderables; 
    };
}

#endif
