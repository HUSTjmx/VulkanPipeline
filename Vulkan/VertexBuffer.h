#pragma once
#ifndef VERTEXBUFFER
#define VERTEXBUFFER
#include"MyBuffer.h"
//�����������
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

	ExcuteVerticeType excuteType;

	VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices);

	VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices, std::vector<uint16_t> indices);

	void createSelf(VkCommandPool commandPool);

	//����IndexBuffer
	void createIndexBuffer(VkCommandPool commandPool);

	//�ͷŶ��㻺��
	void DestroySelf();

	//�ͷ�������ڴ�
	void DestroyMemory();

	/*
	* comment: �ͷ�������Դ�����������㻺�����������ڴ棬�����������������ڴ�
	* Param VkDevice: �߼��豸���
	* return: void
	*/
	void DestroyAll();
};

#endif // !VERTEXBUFFER