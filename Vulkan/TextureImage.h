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

	//�������
	VkImage self;

	//������ͼ
	VkImageView self_view;

	//�����Ӧ���ڴ�
	VkDeviceMemory self_memory;

	//���������
	VkSampler self_sample;

	//ͼ���ַ
	std::string address;

	TextureImage();

	TextureImage(CommandBuffer* command, std::string address);

	void CreateSelf();

	/*
	 * comment: ����ͼ������һ�㷽��
	 * return: void
	 */
	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, 
		VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, MyBuffer* staingBuffer);

	/*
	 * comment: ����ͼƬ����Ĳ���ת��
	 * return: void
	 */
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	/*
	 * comment: �ӻ��������Ƶ�ͼƬ�ĸ�������
	 * return: void
	 */
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	/*
	 * comment: �ͷŲ�����Sample��ImageView��Image��Memory����
	 * return: void
	 */
	void DestroyAll();

	/*
	 * comment: ���������ImageView����
	 * return: void
	 */
	void createTextureImageView(VkFormat format, VkImageAspectFlags aspectFlags);

	/*
	 * comment: ��������Ĳ���������
	 * return: void
	 */
	void createTextureSampler();

	/*
	* comment: ����ͼƬ����������������Ӧ�Ļ�����
	* param: texWidth��������
	* param: texHeight������߶�
	* param: staingBuffer������������
	* return: void
	*/
	void loadTextureToMemory(int& texWidth, int& texHeight, MyBuffer* staingBuffer);

	void ResetImage(std::string address);

};
#endif