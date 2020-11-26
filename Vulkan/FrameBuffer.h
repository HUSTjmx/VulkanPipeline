#pragma once
#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include"CommandBuffer.h"

class FrameBuffer {
public:
	//FrameBuffers
	std::vector<VkFramebuffer> swapChainFramebuffers;

    //�����������
    SwapChain swapChain;
    //��Ⱦ�ܵ�
    GraphicsPipeline graphicsPipeline;
    //��ǰ֡���
    size_t currentFrame = 0;
    //�����Ƿ��ض���
    bool framebufferResized = false;


    FrameBuffer();

    FrameBuffer(SwapChain swapChain, GraphicsPipeline graphicsPipeline, VkImageView depthImageView);

    //�ͷ���Դ
    void Destroy();

    //�ؽ�FrameBuffer
    void ReCreate(VkImageView depthImageView);

    void UpdateCurrentFrame();

private:

    //����FrameBuffers
    void createFramebuffers(VkImageView depthImageView);
};

#endif // !FRAMEBUFFER