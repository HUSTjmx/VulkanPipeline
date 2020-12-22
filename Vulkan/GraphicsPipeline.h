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
    //Vertex Input����
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    //Input Assembly����
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    VkVertexInputBindingDescription bindingDescription = MyVertex::getBindingDescription();
    std::array<VkVertexInputAttributeDescription,5ui64> attributeDescriptions = MyVertex::getAttributeDescriptions();
    //Viewport����
    VkViewport viewport{};
    VkRect2D scissor{};
    VkPipelineViewportStateCreateInfo viewportState{};
    //Rasterizer����
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    //MSAA����
    VkPipelineMultisampleStateCreateInfo multisampling{};
    //Color blending����
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    //depthStencil����
    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    //������ɫ��ģ��
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    //����Shader Module
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //����Render Pass
    void createRenderPass();

    //������Ⱦ�ܵ�
    void createGraphicsPipeline(DescriptorSetLayout* dsl);

    //Vertex Input
    void createVertexInput();

    //Input Assembly
    void createInputAssembly();

    //����viewport
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

    //��ɫ������
    VkPipelineShaderStageCreateInfo* createShaderStages(const std::string vertCode, const std::string fragCode);

};
#endif // !GRAPHICSPIPELINE