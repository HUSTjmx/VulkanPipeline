#pragma once
#ifndef GRAPHICSPIPELINE
#define GRAPHICSPIPELINE

#include"SwapChain.h"
#include"DescriptorSetLayout.h"

class GraphicsPipeline {

public:

    //渲染Pass
    VkRenderPass renderPass;
    //管道layout
    VkPipelineLayout pipelineLayout;
    //图形管道
    VkPipeline self;
    //交换链和相关
    SwapChain* swapChain;

    GraphicsPipeline();

    GraphicsPipeline(SwapChain* swapChain, DescriptorSetLayout* dsl);

    //重建渲染管道和图形管道
    void ReCreate(DescriptorSetLayout* dsl);

    //释放资源
    void Destroy();

private:

    //创建Shader Module
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //创建Render Pass
    void createRenderPass();

    //创建渲染管道
    void createGraphicsPipeline(DescriptorSetLayout* dsl);
};
#endif // !GRAPHICSPIPELINE