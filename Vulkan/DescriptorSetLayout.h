#pragma once
#include"Configuration.h"

class DescriptorSetLayout {
public:
	VkDescriptorSetLayout self;

	DescriptorSetLayout(VkDevice device)
	{
		createDescriptorSetLayout(device);
	}

	/*
	* comment: 创建描述符集的布局
	* partam:  逻辑设备的句柄
	* return: void
	*/
	void createDescriptorSetLayout(VkDevice device) {
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

		VkDescriptorSetLayoutBinding LightLayoutBinding{};
		LightLayoutBinding.binding = 1;
		LightLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		LightLayoutBinding.descriptorCount = 1;
		LightLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		LightLayoutBinding.pImmutableSamplers = nullptr; // Optional

		std::vector<VkDescriptorSetLayoutBinding> ImageLayoutBings;
		for (int i = UNIFORM_NUM;i < UNIFORM_NUM + IMAGE_NUM;i++)
		{
			VkDescriptorSetLayoutBinding samplerLayoutBinding{};
			samplerLayoutBinding.binding = i;
			samplerLayoutBinding.descriptorCount = 1;
			samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			samplerLayoutBinding.pImmutableSamplers = nullptr;
			samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
			ImageLayoutBings.push_back(samplerLayoutBinding);
		}

		std::array<VkDescriptorSetLayoutBinding, UNIFORM_NUM + IMAGE_NUM> bindings ;
		bindings[0] = uboLayoutBinding;
		bindings[1] = LightLayoutBinding;
		for (int i = 0;i < IMAGE_NUM;i++)
		{
			bindings[i + UNIFORM_NUM] = ImageLayoutBings[i];
		}

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &self) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}

	void DestroySelf(VkDevice device)
	{
		vkDestroyDescriptorSetLayout(device, self, nullptr);
	}

};