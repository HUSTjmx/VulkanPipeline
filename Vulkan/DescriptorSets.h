#pragma once
#ifndef DESCRIPTORSETS
#define DESCRIPTORSETS

#include"DescriptorSetLayout.h"
#include"UniformBuffer.h"
#include"TextureImage.h"

class DescriptorSets {
public:
	//²ÎÊý

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> self;

	DescriptorSets();

	void createSelf(SwapChain* swapChain, DescriptorSetLayout* descriptorSetLayout, UniformBuffer* uniformBuffer, TextureImage* textureImages[], UniformBuffer* lightBuffer);

	void createDescriptorPool(SwapChain* swapChain);

	void destroyDescriptorPool(LogicDevice* device);

	void UpdateDescriptorSets(SwapChain* swapChain, UniformBuffer* uniformBuffer, TextureImage* textureImages[], UniformBuffer* lightBuffer);

};
#endif // !DESCRIPTORSETS