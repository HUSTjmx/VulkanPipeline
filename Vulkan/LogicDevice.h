#pragma once
#ifndef LOGICDEVICE
#define LOGICDEVICE

//#include "Configuration.h"
#include "PhysicalDevice.h"

class LogicDevice
{
public:

	VkDevice self;
    //图形队列
    VkQueue graphicsQueue;
    //显示队列
    VkQueue presentQueue;

    LogicDevice();

    LogicDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    //设置逻辑设备
    void createLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    //释放
    void Destroy();
};
#endif // !1