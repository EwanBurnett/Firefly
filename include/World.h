#ifndef _FIREFLY_WORLD_H
#define _FIREFLY_WORLD_H

#include "Object.h"

#include <string>
#include <vector>

namespace Firefly
{
    class World
    {
        public:
            void LoadFromFile(const std::string& filePath);
            const std::vector<IObject*>& GetScene() const; 

        private:
            IObject* ObjectFactory(const std::string& type, void* pElement);
            std::vector<IObject*> m_Objects;
    };
}

#endif
