#include"VertexBuffer.h"

VertexBuffer::VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices)
{
	this->excuteType = Vertice;
	this->swapChain = swapChain;
	this->vertices = vectices;
}

VertexBuffer::VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices, std::vector<uint16_t> indices)
{
	this->excuteType = Index;
	this->indexType = VK_INDEX_TYPE_UINT16;
	this->swapChain = swapChain;
	this->vertices = vectices;
	this->indices = indices;
}

VertexBuffer::VertexBuffer(SwapChain* swapChain, std::vector<MyVertex> vectices, std::vector<uint32_t> indices)
{
	this->excuteType = Index;
	this->indexType = VK_INDEX_TYPE_UINT32;
	this->swapChain = swapChain;
	this->vertices = vectices;
	this->indices_32 = indices;
}

void VertexBuffer::createSelf(VkCommandPool commandPool)
{
	VkDeviceSize bufferSize = sizeof(this->vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);


	void* data;
	vkMapMemory(swapChain->logicDevice->self, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(swapChain->logicDevice->self, stagingBufferMemory);
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, self, vertexBufferMemory);

	copyBuffer(stagingBuffer, self, bufferSize,commandPool);

	vkDestroyBuffer(swapChain->logicDevice->self, stagingBuffer, nullptr);
	vkFreeMemory(swapChain->logicDevice->self, stagingBufferMemory, nullptr);
}

//创建IndexBuffer
void VertexBuffer::createIndexBuffer(VkCommandPool commandPool) {
	if (indexType == VK_INDEX_TYPE_UINT16)
	{
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(swapChain->logicDevice->self, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(swapChain->logicDevice->self, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

		copyBuffer(stagingBuffer, indexBuffer, bufferSize, commandPool);

		vkDestroyBuffer(swapChain->logicDevice->self, stagingBuffer, nullptr);
		vkFreeMemory(swapChain->logicDevice->self, stagingBufferMemory, nullptr);
	}
	else
	{
		VkDeviceSize bufferSize = sizeof(indices_32[0]) * indices_32.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(swapChain->logicDevice->self, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices_32.data(), (size_t)bufferSize);
		vkUnmapMemory(swapChain->logicDevice->self, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

		copyBuffer(stagingBuffer, indexBuffer, bufferSize, commandPool);

		vkDestroyBuffer(swapChain->logicDevice->self, stagingBuffer, nullptr);
		vkFreeMemory(swapChain->logicDevice->self, stagingBufferMemory, nullptr);
	}
}

//释放顶点缓冲
void VertexBuffer::DestroySelf()
{
	vkDestroyBuffer(swapChain->logicDevice->self, self, nullptr);
}

//释放申请的内存
void VertexBuffer::DestroyMemory()
{
	vkFreeMemory(swapChain->logicDevice->self, vertexBufferMemory, nullptr);
}

/*
* comment: 释放所有资源，包括：顶点缓冲和它申请的内存，索引缓冲和它申请的内存
* Param VkDevice: 逻辑设备句柄
* return: void
*/
void VertexBuffer::DestroyAll()
{
	vkDestroyBuffer(swapChain->logicDevice->self, indexBuffer, nullptr);
	vkFreeMemory(swapChain->logicDevice->self, indexBufferMemory, nullptr);

	DestroySelf();
	DestroyMemory();
}