#pragma once
#include "LogicDevice.h"
#include "Configuration.h"
class CreateTool
{
public:
	CreateTool();
	~CreateTool();
	VkImageView createImageView(VkImage image, VkFormat format,VkDevice device, VkImageAspectFlags aspectFlags);

	/*
	 * comment: Ѱ��֧�ֵĸ�ʽ
	 * param: candidates
	 * param: tiling
	 * param: features
	 * return: ���ʵĸ�ʽ
	 */
	static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice device);

	/*
	 * comment: Ѱ�������ͼ�ĺ��ʸ�ʽ
	 * return: void
	 */
	static VkFormat findDepthFormat(VkPhysicalDevice device);

    /*
     * comment: �������ִ�еĿ�ʼ
     * return: void
     */
	VkCommandBuffer beginSingleTimeCommands(LogicDevice* logicDevice, VkCommandPool commandPool);

    /*
     * comment: �������ִ�еĽ���
     * return: void
     */
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, LogicDevice* logicDevice, VkCommandPool commandPool);

    /*
     * comment: Ϊ�������ݼ������ߺ͸�����
     * return: void
     */
    static void SetTangentAndBiForVertex(std::vector<MyVertex>& vertexs, std::vector<uint32_t>& indices);

    /*
    * comment: ������Ķ��������
    * return: void
    */
	static void GetSphereData(std::vector<MyVertex>& vertexs, std::vector<uint16_t>& indices);

	static void GetSphereData(std::vector<MyVertex>& vertexs, std::vector<uint32_t>& indices);

};
