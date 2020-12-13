#pragma once
#ifndef VERTEXBUFFER
#define VERTEXBUFFER
#include"MyBuffer.h"
//顶点绘制类型
enum ExcuteVerticeType {
	Vertice,
	Index
};

class VertexBuffer:MyBuffer{
public:
	VkBuffer self;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<MyVertex> vertices;
	std::vector<uint16_t> indices;
	std::vector<uint32_t> indices_32;

	ExcuteVerticeType excuteType;
	VkIndexType indexType;

	VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices);

	VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices, std::vector<uint16_t> indices);

	VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices, std::vector<uint32_t> indices);

	void createSelf(VkCommandPool commandPool);

	//创建IndexBuffer
	void createIndexBuffer(VkCommandPool commandPool);

	//释放顶点缓冲
	void DestroySelf();

	//释放申请的内存
	void DestroyMemory();

	/*
	* comment: 释放所有资源，包括：顶点缓冲和它申请的内存，索引缓冲和它申请的内存
	* Param VkDevice: 逻辑设备句柄
	* return: void
	*/
	void DestroyAll();
};

#endif // !VERTEXBUFFER