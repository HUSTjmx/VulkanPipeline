#pragma once
#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "LogicDevice.h"

class SwapChain
{

public:

    //�����������
    VkSwapchainKHR self;
    
    std::vector<VkImage> swapChainImages;
   
    VkFormat swapChainImageFormat;
   
    VkExtent2D swapChainExtent;

    //ͼ����ͼ��Image View��
    std::vector<VkImageView> swapChainImageViews;
    //
    LogicDevice* logicDevice;
    PhysicalDevice* physicalDevice;
    GLFWwindow* window;

    SwapChain();

    SwapChain(LogicDevice* logicDevice, PhysicalDevice* physicalDevice, GLFWwindow* window);

    //�ͷ�
    void Destroy(VkDevice device);

    //�ؽ���������Image-View
    void ReCreate();

private:
    //��佻������Format��Ϣ
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    
    //��佻������Present Mode��Ϣ
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    //��佻������Capabilities��Ϣ or Swap Extent
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    //����ͼ����ͼ����Image View
    void createImageViews();

    //����SwapChain
    void createSwapChain();
};

#endif // !SWAPCHAIN_H