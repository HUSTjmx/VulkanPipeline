#pragma once
#ifndef TEXTUREIMAGE_H
#define TEXTUREIMAGE_H

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#endif

#include<string>
#include"CommandBuffer.h"
#include"CreateTool.h"
class TextureImage {
public:

	CommandBuffer* commandBuffer;

	//纹理对象
	VkImage self;

	//纹理视图
	VkImageView self_view;

	//纹理对应的内存
	VkDeviceMemory self_memory;

	//纹理采样器
	VkSampler self_sample;

	//图像地址
	std::string address;

	TextureImage();

	TextureImage(CommandBuffer* command, std::string address);

	void CreateSelf();

	/*
	 * comment: 创建图像对象的一般方法
	 * return: void
	 */
	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, 
		VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, MyBuffer* staingBuffer);

	/*
	 * comment: 处理图片对象的布局转换
	 * return: void
	 */
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	/*
	 * comment: 从缓冲区复制到图片的辅助方法
	 * return: void
	 */
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	/*
	 * comment: 释放采样器Sample，ImageView，Image，Memory对象
	 * return: void
	 */
	void DestroyAll();

	/*
	 * comment: 创建纹理的ImageView对象
	 * return: void
	 */
	void createTextureImageView(VkFormat format, VkImageAspectFlags aspectFlags);

	/*
	 * comment: 创建纹理的采样器对象
	 * return: void
	 */
	void createTextureSampler();

	/*
	* comment: 加载图片，并传入纹理对象对应的缓存区
	* param: texWidth，纹理宽度
	* param: texHeight，纹理高度
	* param: staingBuffer，缓存区对象
	* return: void
	*/
	void loadTextureToMemory(int& texWidth, int& texHeight, MyBuffer* staingBuffer);

	void ResetImage(std::string address);

};
#endif