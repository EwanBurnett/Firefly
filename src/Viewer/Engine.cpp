#include "../../include/Viewer/Engine.h"
#include "../../include/Viewer/Window.h"
#include <cstdio>

void Firefly::Engine::Init(const Window* pWindow)
{
    //Create the Vulkan Instance
    //TODO: Wrap in Instance class
    {
        //Evaluate required Instance extensions
        std::vector<const char*> instanceExtensions = {}; 

        //Retrieve GLFW's required extensions from our window
        instanceExtensions = pWindow->GetRequiredInstanceExtensions(); 

#ifdef _DEBUG
        instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

        //Evaluate required Instance layers
        std::vector<const char*> instanceLayers = {};
#ifdef _DEBUG
        instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
#endif
        printf("[Vulkan]\tCreating Instance\n");
        m_Instance = Helpers::CreateInstance("Firefly", VK_MAKE_API_VERSION(0, FIREFLY_VERSION_MAJOR, FIREFLY_VERSION_MINOR, 0), instanceLayers.data(), instanceLayers.size(), instanceExtensions.data(), instanceExtensions.size(), nullptr);
    }

#ifdef _DEBUG
    m_DebugLogger = Helpers::CreateDebugLogger(m_Instance, nullptr);
#endif

    m_PhysicalDevice = Helpers::AcquirePhysicalDevice(m_Instance, nullptr, nullptr);

    m_Surface = Helpers::CreateWindowSurface(m_Instance, pWindow->GLFWHandle(), nullptr);
    m_QueueFamilyIndices = Helpers::GetQueueFamilyProperties(m_PhysicalDevice, &m_Surface);
    Helpers::SwapChainSupportDetails supportDetails = Helpers::QuerySwapChainSupport(m_PhysicalDevice, m_Surface);

    //Create the Logical Device
    {
        std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        m_Device = Helpers::CreateLogicalDevice(m_PhysicalDevice, m_QueueFamilyIndices, supportDetails, deviceExtensions.data(), deviceExtensions.size(), nullptr);
    }

    //Retrieve the Required Queues
    {
        for (auto& pair : m_QueueFamilyIndices.Graphics)
        {
            const size_t& index = pair.first;
            const size_t& count = pair.second;

            for (size_t i = 0; i < count; i++) {
                m_GraphicsQueues.push_back({});
                m_GraphicsQueues.back().first = index;
                vkGetDeviceQueue(m_Device, index, i, &m_GraphicsQueues.back().second);
            }
        }

        for (auto& pair : m_QueueFamilyIndices.Presentation)
        {
            const size_t& index = pair.first;
            const size_t& count = pair.second;

            for (size_t i = 0; i < count; i++) {
                m_PresentationQueues.push_back({});
                m_PresentationQueues.back().first = index;
                vkGetDeviceQueue(m_Device, index, i, &m_PresentationQueues.back().second);
            }
        }
    }

    //Create the Swapchain
    {
        m_SwapchainFormat = Helpers::SelectSwapChainFormat(supportDetails.formats.size(), supportDetails.formats.data()); 
        VkPresentModeKHR presentMode = Helpers::SelectSwapChainPresentMode(supportDetails.presentMode.size(), supportDetails.presentMode.data()); 
        m_SwapchainExtents = Helpers::SelectSwapChainExtent(supportDetails.capabilities, pWindow->GLFWHandle());

        m_Swapchain = Helpers::CreateSwapChain(m_Device, m_Surface, m_SwapchainFormat, presentMode, m_SwapchainExtents, supportDetails.capabilities, nullptr);

        uint32_t swapchainImageCount = 0; 
        vkGetSwapchainImagesKHR(m_Device, m_Swapchain, &swapchainImageCount, nullptr);
        m_SwapchainImages.resize(swapchainImageCount);
        vkGetSwapchainImagesKHR(m_Device, m_Swapchain, &swapchainImageCount, m_SwapchainImages.data());

        m_SwapchainImageViews = Helpers::CreateImageViews(m_Device, m_SwapchainImages, m_SwapchainFormat.format, nullptr);

    }

}

void Firefly::Engine::Shutdown()
{
    vkDeviceWaitIdle(m_Device); 

    Helpers::DestroySwapChain(m_Device, m_Swapchain);
    Helpers::DestroyLogicalDevice(m_Device, nullptr);
    Helpers::DestroyWindowSurface(m_Instance, m_Surface, nullptr);
#ifdef DEBUG
    Helpers::DestroyDebugLogger(m_Instance, m_DebugLogger, nullptr);
#endif
    Helpers::DestroyInstance(m_Instance, nullptr);
}
