#include"FrameBuffer.h"

FrameBuffer::FrameBuffer()
{

}

FrameBuffer::FrameBuffer(SwapChain swapChain, GraphicsPipeline graphicsPipeline, VkImageView depthImageView)
{
    this->swapChain = swapChain;
    this->graphicsPipeline = graphicsPipeline;
    createFramebuffers(depthImageView);
}

//释放资源
void FrameBuffer::Destroy()
{
    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(swapChain.logicDevice->self, framebuffer, nullptr);
    }
}

//重建FrameBuffer
void FrameBuffer::ReCreate(VkImageView depthImageView)
{
    createFramebuffers(depthImageView);
}

void FrameBuffer::UpdateCurrentFrame()
{
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

//创建FrameBuffers
void FrameBuffer::createFramebuffers(VkImageView depthImageView) {
    swapChainFramebuffers.resize(swapChain.swapChainImageViews.size());
    for (size_t i = 0; i < swapChain.swapChainImageViews.size(); i++) {
        std::array<VkImageView, 2> attachments = {
            swapChain.swapChainImageViews[i],
            depthImageView
        };


        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = graphicsPipeline.renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChain.swapChainExtent.width;
        framebufferInfo.height = swapChain.swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(swapChain.logicDevice->self, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}