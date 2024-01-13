#ifndef _FIREFLY_WINDOW_H
#define _FIREFLY_WINDOW_H

#include <GLFW/glfw3.h>
#include <vector> 

#include <cstdint> 

namespace Firefly {
    class Window {
    public: 
        Window(); 
        ~Window(); 

        bool Create(const uint16_t width, const uint16_t height, const char* title);

        void Close(); 
        /**
         * @brief Polls OS events
         * @return True if all events have been polled, false if the window has been closed. 
        */
        bool PollEvents(); 

        bool SetSize(const uint16_t width, const uint16_t height);

        std::vector<const char*> GetRequiredInstanceExtensions() const;
        GLFWwindow* GLFWHandle() const; 

    private:
        uint16_t m_Width;   //TODO: Replace with a Vector2 struct
        uint16_t m_Height; 
        const char* m_Title; 
        GLFWwindow* m_pHandle; 

    };
}

#endif