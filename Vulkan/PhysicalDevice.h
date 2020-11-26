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

    //ѡ�������豸
    void pickPhysicalDevice();


private:
    //�ж��豸�Ƿ����
    bool isDeviceSuitable(VkPhysicalDevice device);

    //�����չ֧��
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};
#endif // !PHYSICALDEVICE