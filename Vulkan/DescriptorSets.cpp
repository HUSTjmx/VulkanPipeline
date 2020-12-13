#include"DescriptorSets.h"

DescriptorSets::DescriptorSets()
{

}

void DescriptorSets::createSelf(SwapChain* swapChain, DescriptorSetLayout* descriptorSetLayout
	, UniformBuffer* uniformBuffer, TextureImage* textureImages[], UniformBuffer* lightBuffer)
{
	std::vector<VkDescriptorSetLayout> layouts(swapChain->swapChainImages.size(), descriptorSetLayout->self);
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChain->swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

	self.resize(swapChain->swapChainImages.size());
	if (vkAllocateDescriptorSets(swapChain->logicDevice->self, &allocInfo, self.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	UpdateDescriptorSets(swapChain, uniformBuffer, textureImages,lightBuffer);
}

void DescriptorSets::UpdateDescriptorSets(SwapChain* swapChain, UniformBuffer* uniformBuffer, TextureImage* textureImages[], UniformBuffer* lightBuffer)
{
	for (size_t i = 0; i < swapChain->swapChainImages.size(); i++) {
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = uniformBuffer->selfs[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(CameraOfUniformBufferObject);

		VkDescriptorBufferInfo LightInfo{};
		LightInfo.buffer = lightBuffer->selfs[i];
		LightInfo.offset = 0;
		LightInfo.range = sizeof(PointLightOfUniformBufferObject);

		VkDescriptorImageInfo imageInfos[IMAGE_NUM];
		for (int j = 0;j < IMAGE_NUM;j++)
		{
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = textureImages[j]->self_view;
			imageInfo.sampler = textureImages[j]->self_sample;
			imageInfos[j] = imageInfo;
		}

		std::array<VkWriteDescriptorSet, UNIFORM_NUM + IMAGE_NUM> descriptorWrites{};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = self[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = self[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pBufferInfo = &LightInfo;

		for (int j = 0;j < IMAGE_NUM;j++)
		{
			descriptorWrites[UNIFORM_NUM + j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[UNIFORM_NUM + j].dstSet = self[i];
			descriptorWrites[UNIFORM_NUM + j].dstBinding = 2 + j;
			descriptorWrites[UNIFORM_NUM + j].dstArrayElement = 0;
			descriptorWrites[UNIFORM_NUM + j].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[UNIFORM_NUM + j].descriptorCount = 1;
			descriptorWrites[UNIFORM_NUM + j].pImageInfo = &imageInfos[j];
		}

		vkUpdateDescriptorSets(swapChain->logicDevice->self, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

	}
}

void DescriptorSets::createDescriptorPool(SwapChain* swapChain) {
	std::array<VkDescriptorPoolSize, UNIFORM_NUM + IMAGE_NUM> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChain->swapChainImages.size());
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChain->swapChainImages.size());
	for (int i = 0;i < IMAGE_NUM;i++)
	{
		poolSizes[i + UNIFORM_NUM].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[i + UNIFORM_NUM].descriptorCount = static_cast<uint32_t>(swapChain->swapChainImages.size());
	}

	VkDescriptorPoolCreateInfo poolInfo {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(swapChain->swapChainImages.size());

	if (vkCreateDescriptorPool(swapChain->logicDevice->self, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void DescriptorSets::destroyDescriptorPool(LogicDevice* device)
{
	vkDestroyDescriptorPool(device->self, descriptorPool, nullptr);
}