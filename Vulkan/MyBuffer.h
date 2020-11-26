#pragma once
#ifndef MYBUFFER_H
#define  MYBUFFER_H

#include"CreateTool.h"
#include"SwapChain.h"

class MyBuffer {
public:
	VkBuffer self;
	VkDeviceMemory self_memory;

	SwapChain* swapChain;

	MyBuffer();

	MyBuffer(SwapChain* swapChain);

	//寻找合适的内存类型
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	/*
	* comment: 创建内存的辅助函数
	* Param VkDeviceSize: 缓冲区大小
	* Param VkBufferUsageFlags: 缓冲区的使用目的
	* Param VkMemoryPropertyFlags: 缓冲区的使用范围，独有或者多个队列族之间共享
	* Param VkBuffer: 缓冲区对象
	* Param VkDeviceMemory: 内存
	* Param VkDevice: 逻辑设备句柄
	* return: void
	*/
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool);

	void DestroySelfAndMemory();
};

#endif // DEBUG