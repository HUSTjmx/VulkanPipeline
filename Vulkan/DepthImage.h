#pragma once
#include"TextureImage.h"
class DepthImage : public TextureImage {
public:
	/*
	 * comment: ������Ȼ������Դ
	 * return: void
	 */
	void createDepthResources();

	/*
	 * comment: Ѱ��֧�ֵĸ�ʽ
	 * param: candidates
	 * param: tiling
	 * param: features
	 * return: ���ʵĸ�ʽ
	 */
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	/*
	 * comment: Ѱ�������ͼ�ĺ��ʸ�ʽ
	 * return: void
	 */
	VkFormat findDepthFormat();

	/*
	 * comment: �ж���ѡ����ȸ�ʽ�Ƿ����stencil component
	 * return: bool
	 */
	bool hasStencilComponent(VkFormat format);
};
