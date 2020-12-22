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
    //Vertex Input对象
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    //Input Assembly对象
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    VkVertexInputBindingDescription bindingDescription = MyVertex::getBindingDescription();
    std::array<VkVertexInputAttributeDescription,5ui64> attributeDescriptions = MyVertex::getAttributeDescriptions();
    //Viewport对象
    VkViewport viewport{};
    VkRect2D scissor{};
    VkPipelineViewportStateCreateInfo viewportState{};
    //Rasterizer对象
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    //MSAA对象
    VkPipelineMultisampleStateCreateInfo multisampling{};
    //Color blending对象
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    //depthStencil对象
    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    //两个着色器模块
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    //创建Shader Module
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //创建Render Pass
    void createRenderPass();

    //创建渲染管道
    void createGraphicsPipeline(DescriptorSetLayout* dsl);

    //Vertex Input
    void createVertexInput();

    //Input Assembly
    void createInputAssembly();

    //创建viewport
    void createViewPort();

    //Rasterizer
    void createRasterizer();

    //MSAA
    void createMSAA();

    //Color blending
    void createColorBlending();

    //pipeline Layout
    void createPipelineLayout(DescriptorSetLayout* dsl);

    //DepthStencilState
    void createDepthStencilState();

    //createGraphicsPipeline info struct
    void createGraphicsPipelineStruct();

    //着色器配置
    VkPipelineShaderStageCreateInfo* createShaderStages(const std::string vertCode, const std::string fragCode);

};
#endif // !GRAPHICSPIPELINE