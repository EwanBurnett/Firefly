#ifndef _FIREFLY_OBJECT_H
#define _FIREFLY_OBJECT_H

#include "Vector3.h"
#include <vector>
#include <cstdint>

namespace Firefly
{
    class IObject
    {
        public:
            IObject();
            IObject(uint32_t type, uint32_t id, IObject* pParent);
            ~IObject(); 
            
            void AddChild(uint32_t type, uint32_t id);
            
            IObject* GetParent() const;
            std::vector<IObject*> GetChildren() const;
            
            uint32_t GetID() const;
            uint32_t GetType() const; 

            void SetPosition(const Vector3& position);
            Vector3 GetPosition() const; 
        private:
            uint32_t m_Type;
            uint32_t m_ID;
            IObject* m_Parent;
            std::vector<IObject*> m_Children;

            Vector3 m_Position;
    };

}
#endif
