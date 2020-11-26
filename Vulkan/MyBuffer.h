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

	//Ѱ�Һ��ʵ��ڴ�����
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	/*
	* comment: �����ڴ�ĸ�������
	* Param VkDeviceSize: ��������С
	* Param VkBufferUsageFlags: ��������ʹ��Ŀ��
	* Param VkMemoryPropertyFlags: ��������ʹ�÷�Χ�����л��߶��������֮�乲��
	* Param VkBuffer: ����������
	* Param VkDeviceMemory: �ڴ�
	* Param VkDevice: �߼��豸���
	* return: void
	*/
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool);

	void DestroySelfAndMemory();
};

#endif // DEBUG