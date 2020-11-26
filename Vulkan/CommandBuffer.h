#pragma once
#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H
#include"GraphicsPipeline.h"
#include"VertexBuffer.h"

class CommandBuffer {
public:
    //命令池
    VkCommandPool commandPool;
    //命令缓冲区
    std::vector<VkCommandBuffer> commandBuffers;
    //同步信号量
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    //渲染管道
    GraphicsPipeline* graphicsPipeline;
    //
    PhysicalDevice* physicalDevice;

    CommandBuffer();

    //不包含自身的初始化
    CommandBuffer(PhysicalDevice* physicalDevice,GraphicsPipeline* graphicsPipeline);

    //创建命令池
    void createCommandPool();

    //创建同步信号量
    void createSyncObjects();

    //创建命令缓冲区(为SwapChain中的每一个Image创建一个) & 重建
    void Create(std::vector<VkFramebuffer> swapChainFramebuffers , std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferByVertex(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer
       , std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferByIndex(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer, std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferForTest(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer1, VertexBuffer* vertexBuffer2, std::vector<VkDescriptorSet>& descriptorSets);

    //绘制所有对象
    void excuteCommandBufferForAll(std::vector<VkFramebuffer> swapChainFramebuffers, std::vector<VertexBuffer*> vertexBuffer, std::vector<VkDescriptorSet>& descriptorSets);

    //释放资源(信号量和命令池)
    void DestroyOthers();

    //释放自身
    void DestroySelf();

private:
  

};

#endif // !COMMANDBUFFER_H