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
	 * comment: 寻找支持的格式
	 * param: candidates
	 * param: tiling
	 * param: features
	 * return: 合适的格式
	 */
	static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice device);

	/*
	 * comment: 寻找深度贴图的合适格式
	 * return: void
	 */
	static VkFormat findDepthFormat(VkPhysicalDevice device);

    /*
     * comment: 命令缓冲区执行的开始
     * return: void
     */
	VkCommandBuffer beginSingleTimeCommands(LogicDevice* logicDevice, VkCommandPool commandPool);

    /*
     * comment: 命令缓冲区执行的结束
     * return: void
     */
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, LogicDevice* logicDevice, VkCommandPool commandPool);

    /*
     * comment: 为顶点数据计算切线和副法线
     * return: void
     */
    static void SetTangentAndBiForVertex(std::vector<MyVertex>& vertexs, std::vector<uint32_t>& indices);

    /*
    * comment: 计算球的顶点和索引
    * return: void
    */
	static void GetSphereData(std::vector<MyVertex>& vertexs, std::vector<uint16_t>& indices);

	static void GetSphereData(std::vector<MyVertex>& vertexs, std::vector<uint32_t>& indices);

};
