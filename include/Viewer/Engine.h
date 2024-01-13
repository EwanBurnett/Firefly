#ifndef _FIREFLY_ENGINE_H
#define _FIREFLY_ENGINE_H

#include "VkHelpers.h"
#include <vector>

namespace Firefly {
    class Window;

    class Engine {
    public: 
        void Init(const Window* window);
        void Shutdown(); 

        void BeginFrame(); 
        void EndFrame(); 
    private:
        VkInstance m_Instance; 
        VkPhysicalDevice m_PhysicalDevice; 
        VkDevice m_Device; 

        //TODO: Encapsulate in a Swapchain class
        VkSurfaceKHR m_Surface; 
        VkSwapchainKHR m_Swapchain;
        std::vector<VkImage> m_SwapchainImages;
        std::vector<VkImageView> m_SwapchainImageViews;
        VkSurfaceFormatKHR m_SwapchainFormat; 
        VkExtent2D m_SwapchainExtents; 
        
        Helpers::QueueFamilyIndices m_QueueFamilyIndices; 
        std::vector<std::pair<size_t, VkQueue>> m_GraphicsQueues;
        std::vector<std::pair<size_t, VkQueue>> m_PresentationQueues;

        VkCommandPool m_CommandPool;
        VkCommandBuffer m_CmdBuffer;    //Handles presentation

        VkRenderPass m_RenderPass; 
        std::vector<VkFramebuffer> m_FrameBuffers;

        VkFence m_RenderFence; 
        VkSemaphore m_ImageAvailable; 
        VkSemaphore m_RenderFinished;
        uint32_t m_FrameIndex; 
#ifdef _DEBUG
        VkDebugUtilsMessengerEXT m_DebugLogger; 
#endif


    };
}
#endif