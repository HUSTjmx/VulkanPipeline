#pragma once
#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include"CommandBuffer.h"

class FrameBuffer {
public:
	//FrameBuffers
	std::vector<VkFramebuffer> swapChainFramebuffers;

    //交换链和相关
    SwapChain swapChain;
    //渲染管道
    GraphicsPipeline graphicsPipeline;
    //当前帧编号
    size_t currentFrame = 0;
    //窗口是否重定义
    bool framebufferResized = false;


    FrameBuffer();

    FrameBuffer(SwapChain swapChain, GraphicsPipeline graphicsPipeline, VkImageView depthImageView);

    //释放资源
    void Destroy();

    //重建FrameBuffer
    void ReCreate(VkImageView depthImageView);

    void UpdateCurrentFrame();

private:

    //创建FrameBuffers
    void createFramebuffers(VkImageView depthImageView);
};

#endif // !FRAMEBUFFER