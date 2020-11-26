#pragma once
#ifndef LOGICDEVICE
#define LOGICDEVICE

//#include "Configuration.h"
#include "PhysicalDevice.h"

class LogicDevice
{
public:

	VkDevice self;
    //ͼ�ζ���
    VkQueue graphicsQueue;
    //��ʾ����
    VkQueue presentQueue;

    LogicDevice();

    LogicDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    //�����߼��豸
    void createLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    //�ͷ�
    void Destroy();
};
#endif // !1