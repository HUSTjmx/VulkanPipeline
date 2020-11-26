#pragma once
#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "LogicDevice.h"

class SwapChain
{

public:

    //交换链和相关
    VkSwapchainKHR self;
    
    std::vector<VkImage> swapChainImages;
   
    VkFormat swapChainImageFormat;
   
    VkExtent2D swapChainExtent;

    //图像视图（Image View）
    std::vector<VkImageView> swapChainImageViews;
    //
    LogicDevice* logicDevice;
    PhysicalDevice* physicalDevice;
    GLFWwindow* window;

    SwapChain();

    SwapChain(LogicDevice* logicDevice, PhysicalDevice* physicalDevice, GLFWwindow* window);

    //释放
    void Destroy(VkDevice device);

    //重建交换链和Image-View
    void ReCreate();

private:
    //填充交换链的Format信息
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    
    //填充交换链的Present Mode信息
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    //填充交换链的Capabilities信息 or Swap Extent
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    //创建图像视图——Image View
    void createImageViews();

    //创建SwapChain
    void createSwapChain();
};

#endif // !SWAPCHAIN_H