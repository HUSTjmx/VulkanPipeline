#include"MyBuffer.h"

MyBuffer::MyBuffer()
{

}

MyBuffer::MyBuffer(SwapChain* swapChain)
{
	this->swapChain = swapChain;
}

//Ѱ�Һ��ʵ��ڴ�����
uint32_t MyBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(swapChain->physicalDevice->self, &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type!");
}

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
void MyBuffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(swapChain->logicDevice->self, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(swapChain->logicDevice->self, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(swapChain->logicDevice->self, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(swapChain->logicDevice->self, buffer, bufferMemory, 0);

}

void MyBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size,VkCommandPool commandPool) {
	CreateTool* ct = new CreateTool();
	VkCommandBuffer commandBuffer = ct->beginSingleTimeCommands(swapChain->logicDevice, commandPool);
	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
	ct->endSingleTimeCommands(commandBuffer,swapChain->logicDevice, commandPool);
}

void MyBuffer::DestroySelfAndMemory()
{
	vkDestroyBuffer(swapChain->logicDevice->self, self, nullptr);
	vkFreeMemory(swapChain->logicDevice->self, self_memory, nullptr);
}