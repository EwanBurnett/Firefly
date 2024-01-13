#include "../../include/Viewer/Viewer.h"

Firefly::Viewer::Viewer()
{
}

Firefly::Viewer::~Viewer()
{
}

void Firefly::Viewer::Init(const Window* pWindow)
{
    m_Engine.Init(pWindow); 
}

void Firefly::Viewer::Shutdown()
{
}
