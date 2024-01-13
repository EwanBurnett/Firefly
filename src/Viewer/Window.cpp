#include "../../include/Viewer/Window.h"
#include <cstdio> //TODO: Replace with Logger


Firefly::Window::Window()
{
    m_Width = 0; 
    m_Height = 0; 
    m_Title = "";
    m_pHandle = nullptr; 
}

Firefly::Window::~Window()
{
    glfwDestroyWindow(m_pHandle);
}

bool Firefly::Window::Create(const uint16_t width, const uint16_t height, const char* title)
{
    m_Width = width; 
    m_Height = height;
    m_Title = title; 

    printf("[Viewer]\tCreating window %s [%d x %d]\n", m_Title, m_Width, m_Height);
    m_pHandle = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    if (!m_pHandle) {
        return false; 
    }
    return true;
}

void Firefly::Window::Close()
{
    glfwSetWindowShouldClose(m_pHandle, true);
}

bool Firefly::Window::PollEvents()
{
    if (glfwWindowShouldClose(m_pHandle)) {
        return false; 
    }

    glfwPollEvents();
    return true;
}

bool Firefly::Window::SetSize(const uint16_t width, const uint16_t height)
{
    m_Width = width;
    m_Height = height; 

    if (!m_pHandle) { //If the handle is nullptr, then the window was never created. 
        return false; 
    }

    glfwSetWindowSize(m_pHandle, m_Width, m_Height); 
    return true; 
}
