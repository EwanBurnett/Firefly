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

    //Create our Command Pool
    m_CommandPool = Helpers::CreateCommandPool(m_Device, m_GraphicsQueues[0].first);
    m_CmdBuffer = Helpers::CreateCommandBuffer(m_Device, m_CommandPool);

    m_RenderFence = Helpers::CreateSyncFence(m_Device); 
    m_ImageAvailable = Helpers::CreateSyncSemaphore(m_Device);
    m_RenderFinished = Helpers::CreateSyncSemaphore(m_Device); 

    m_RenderPass = Helpers::CreateRenderPass(m_Device, m_SwapchainFormat.format); 
    m_FrameBuffers = Helpers::CreateFrameBuffers(m_Device, m_SwapchainImageViews.size(), m_SwapchainExtents, m_SwapchainImageViews.data(), m_RenderPass); 

}

void Firefly::Engine::Shutdown()
{
    vkDeviceWaitIdle(m_Device); 

    Helpers::DestroySwapChain(m_Device, m_Swapchain);
    Helpers::DestroyLogicalDevice(m_Device, nullptr);
    Helpers::DestroyWindowSurface(m_Instance, m_Surface, nullptr);
#ifdef _DEBUG
    Helpers::DestroyDebugLogger(m_Instance, m_DebugLogger, nullptr);
#endif
    Helpers::DestroyInstance(m_Instance, nullptr);
}

void Firefly::Engine::BeginFrame()
{
    //Wait for the current frame 
    vkWaitForFences(m_Device, 1, &m_RenderFence, VK_TRUE, UINT64_MAX);
    vkResetFences(m_Device, 1, &m_RenderFence);

    vkAcquireNextImageKHR(m_Device, m_Swapchain, UINT64_MAX, m_ImageAvailable, VK_NULL_HANDLE, &m_FrameIndex);
    vkResetCommandBuffer(m_CmdBuffer, 0);

    //Begin the Command Buffer
    VkCommandBufferBeginInfo beginInfo = {}; 
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO; 
    beginInfo.pNext = nullptr; 
    beginInfo.pInheritanceInfo = nullptr;
    beginInfo.flags = 0;

    vkBeginCommandBuffer(m_CmdBuffer, &beginInfo);

    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.pNext = nullptr;
    renderPassBeginInfo.renderPass = m_RenderPass;
    renderPassBeginInfo.framebuffer = m_FrameBuffers[m_FrameIndex];
    renderPassBeginInfo.renderArea.offset = { 0, 0 };
    renderPassBeginInfo.renderArea.extent = m_SwapchainExtents;

    //VkClearValue clearColour = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue clearColour = { {{52.0f / 255.99f, 49.0f / 255.99f, 49.0f / 255.99, 1.0f}} };
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColour;

    vkCmdBeginRenderPass(m_CmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void Firefly::Engine::EndFrame()
{
    vkCmdEndRenderPass(m_CmdBuffer);
    vkEndCommandBuffer(m_CmdBuffer);

    //Submit the recorded commands
    VkSemaphore waitFor[] = { m_ImageAvailable };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitFor;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_CmdBuffer;

    VkSemaphore signalSemaphores[] = { m_RenderFinished };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(m_GraphicsQueues[0].second, 1, &submitInfo, m_RenderFence) != VK_SUCCESS) {
        //throw std::runtime_error("Failed to submit command buffer!\n");
    }


    //Present 
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR SwapChains[] = { m_Swapchain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = SwapChains;
    presentInfo.pImageIndices = &m_FrameIndex;
    presentInfo.pResults = nullptr;

    vkQueuePresentKHR(m_PresentationQueues[0].second, &presentInfo);

}
