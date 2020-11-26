#pragma once
#ifndef PHYSICALDEVICE
#define PHYSICALDEVICE

#include"StaticFunc.h"
class PhysicalDevice
{

public:
    VkPhysicalDevice self = VK_NULL_HANDLE;
    VkSurfaceKHR surface;
    VkInstance instance;

    PhysicalDevice();

    PhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

    //选择物理设备
    void pickPhysicalDevice();


private:
    //判断设备是否合适
    bool isDeviceSuitable(VkPhysicalDevice device);

    //检查扩展支持
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};
#endif // !PHYSICALDEVICE