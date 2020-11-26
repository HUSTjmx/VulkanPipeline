#pragma once
#include"TextureImage.h"
class DepthImage : public TextureImage {
public:
	/*
	 * comment: 设置深度缓存的资源
	 * return: void
	 */
	void createDepthResources();

	/*
	 * comment: 寻找支持的格式
	 * param: candidates
	 * param: tiling
	 * param: features
	 * return: 合适的格式
	 */
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	/*
	 * comment: 寻找深度贴图的合适格式
	 * return: void
	 */
	VkFormat findDepthFormat();

	/*
	 * comment: 判断所选的深度格式是否包含stencil component
	 * return: bool
	 */
	bool hasStencilComponent(VkFormat format);
};
