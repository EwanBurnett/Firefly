#ifndef _FIREFLY_VIEWER_H
#define _FIREFLY_VIEWER_H

#include "Engine.h"

namespace Firefly {
    class Window; 

    class Viewer {
    public: 
        Viewer(); 
        ~Viewer();

        void Init(const Window* pWindow); 
        void Shutdown(); 

        void BeginFrame(); 
        void EndFrame(); 

    private: 
        Engine m_Engine; 
    };
}

#endif