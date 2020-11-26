#pragma once
#ifndef GRAPHICSPIPELINE
#define GRAPHICSPIPELINE

#include"SwapChain.h"
#include"DescriptorSetLayout.h"

class GraphicsPipeline {

public:

    //��ȾPass
    VkRenderPass renderPass;
    //�ܵ�layout
    VkPipelineLayout pipelineLayout;
    //ͼ�ιܵ�
    VkPipeline self;
    //�����������
    SwapChain* swapChain;

    GraphicsPipeline();

    GraphicsPipeline(SwapChain* swapChain, DescriptorSetLayout* dsl);

    //�ؽ���Ⱦ�ܵ���ͼ�ιܵ�
    void ReCreate(DescriptorSetLayout* dsl);

    //�ͷ���Դ
    void Destroy();

private:

    //����Shader Module
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //����Render Pass
    void createRenderPass();

    //������Ⱦ�ܵ�
    void createGraphicsPipeline(DescriptorSetLayout* dsl);
};
#endif // !GRAPHICSPIPELINE