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

void Firefly::Viewer::BeginFrame()
{
    m_Engine.BeginFrame(); 
}

void Firefly::Viewer::EndFrame()
{
    m_Engine.EndFrame(); 
}
