#include"TextureImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
TextureImage::TextureImage()
{

}

TextureImage::TextureImage(CommandBuffer* command, std::string address)
{
    this->commandBuffer = command;
    this->address = address;
}

void TextureImage::CreateSelf()
{
    int texWidth, texHeight;
    MyBuffer* staingBuffer = new MyBuffer(this->commandBuffer->graphicsPipeline->swapChain);
    loadTextureToMemory(texWidth, texHeight, staingBuffer);

    CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT
        , VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, self, self_memory,staingBuffer);
    
    transitionImageLayout(self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(staingBuffer->self, self, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    transitionImageLayout(self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    staingBuffer->DestroySelfAndMemory();
}

void TextureImage::CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
    VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, MyBuffer* staingBuffer)
{
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(width);
    imageInfo.extent.height = static_cast<uint32_t>(height);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.flags = 0; // Optional

    if (vkCreateImage(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, &imageInfo, nullptr, &self) != VK_SUCCESS) {
        throw std::runtime_error("failed to create image!");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, self, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = staingBuffer->findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate image memory!");
    }

    vkBindImageMemory(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, image, imageMemory, 0);
}

void TextureImage::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
    CreateTool* ct = new CreateTool();
    VkCommandBuffer vkComBuff = ct->beginSingleTimeCommands(commandBuffer->graphicsPipeline->swapChain->logicDevice, commandBuffer->commandPool);

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;
    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        vkComBuff,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );


    ct->endSingleTimeCommands(vkComBuff, commandBuffer->graphicsPipeline->swapChain->logicDevice, commandBuffer->commandPool);
}

void TextureImage::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
    CreateTool* ct = new CreateTool();
    VkCommandBuffer vkComBuff = ct->beginSingleTimeCommands(commandBuffer->graphicsPipeline->swapChain->logicDevice,commandBuffer->commandPool);

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(
        vkComBuff,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    ct->endSingleTimeCommands(vkComBuff, commandBuffer->graphicsPipeline->swapChain->logicDevice, commandBuffer->commandPool);
}

void TextureImage::DestroyAll()
{
    vkDestroySampler(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, self_sample, nullptr);
    vkDestroyImageView(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, self_view, nullptr);
    vkDestroyImage(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, self, nullptr);
    vkFreeMemory(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, self_memory, nullptr);
}

void TextureImage::createTextureImageView(VkFormat format, VkImageAspectFlags aspectFlags)
{
    CreateTool* ct = new CreateTool();
    self_view = ct->createImageView(self, format, commandBuffer->graphicsPipeline->swapChain->logicDevice->self, aspectFlags);
}

void TextureImage::createTextureSampler()
{
    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;

    if (vkCreateSampler(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, &samplerInfo, nullptr, &self_sample) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

void TextureImage::loadTextureToMemory(int& texWidth, int& texHeight, MyBuffer* staingBuffer)
{
    if (address.empty())
    {
        throw std::runtime_error("there is no address of image");
    }
    const char* c_s = address.c_str();
    int texChannels;
    stbi_uc* pixels = stbi_load(c_s, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }
    staingBuffer->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        , staingBuffer->self, staingBuffer->self_memory);

    void* data;
    vkMapMemory(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, staingBuffer->self_memory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(commandBuffer->graphicsPipeline->swapChain->logicDevice->self, staingBuffer->self_memory);

    stbi_image_free(pixels);
}

void TextureImage::ResetImage(std::string address)
{
    this->address = address;
    CreateSelf();
}