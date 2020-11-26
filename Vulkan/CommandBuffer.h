#pragma once
#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H
#include"GraphicsPipeline.h"
#include"VertexBuffer.h"

class CommandBuffer {
public:
    //�����
    VkCommandPool commandPool;
    //�������
    std::vector<VkCommandBuffer> commandBuffers;
    //ͬ���ź���
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    //��Ⱦ�ܵ�
    GraphicsPipeline* graphicsPipeline;
    //
    PhysicalDevice* physicalDevice;

    CommandBuffer();

    //����������ĳ�ʼ��
    CommandBuffer(PhysicalDevice* physicalDevice,GraphicsPipeline* graphicsPipeline);

    //���������
    void createCommandPool();

    //����ͬ���ź���
    void createSyncObjects();

    //�����������(ΪSwapChain�е�ÿһ��Image����һ��) & �ؽ�
    void Create(std::vector<VkFramebuffer> swapChainFramebuffers , std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferByVertex(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer
       , std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferByIndex(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer, std::vector<VkDescriptorSet>& descriptorSets);

    void excuteCommandBufferForTest(std::vector<VkFramebuffer> swapChainFramebuffers, VertexBuffer* vertexBuffer1, VertexBuffer* vertexBuffer2, std::vector<VkDescriptorSet>& descriptorSets);

    //�������ж���
    void excuteCommandBufferForAll(std::vector<VkFramebuffer> swapChainFramebuffers, std::vector<VertexBuffer*> vertexBuffer, std::vector<VkDescriptorSet>& descriptorSets);

    //�ͷ���Դ(�ź����������)
    void DestroyOthers();

    //�ͷ�����
    void DestroySelf();

private:
  

};

#endif // !COMMANDBUFFER_H