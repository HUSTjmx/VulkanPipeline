#include"CreateTool.h"

CreateTool::CreateTool()
{
}

CreateTool::~CreateTool()
{
}


/*
 * comment: 创建ImageView对象
 * param:  Image 图像对象
 * param:  format 图像格式
 * param:  device 逻辑设备句柄
 * return: VkImageView
 */
VkImageView CreateTool::createImageView(VkImage image, VkFormat format, VkDevice device, VkImageAspectFlags aspectFlags)
{
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture image view!");
    }

    return imageView;
}

VkFormat CreateTool::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features,VkPhysicalDevice device)
{
    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(device, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("failed to find supported format!");
}

VkFormat CreateTool::findDepthFormat(VkPhysicalDevice device)
{
    return findSupportedFormat(
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
        device
    );
}

//命令缓冲区执行的过程
VkCommandBuffer CreateTool::beginSingleTimeCommands(LogicDevice* logicDevice, VkCommandPool commandPool) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(logicDevice->self, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void CreateTool::endSingleTimeCommands(VkCommandBuffer commandBuffer, LogicDevice* logicDevice, VkCommandPool commandPool) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(logicDevice->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(logicDevice->graphicsQueue);

    vkFreeCommandBuffers(logicDevice->self, commandPool, 1, &commandBuffer);
}

void CreateTool::SetTangentAndBiForVertex(std::vector<MyVertex>& vertexs, std::vector<uint32_t>& indices)
{
    for (int i = 0;i < indices.size();i += 3)
    {
        // - triangle 1
        glm::vec3 edge1 = vertexs[indices[i + 1]].pos - vertexs[indices[i]].pos;
        glm::vec3 edge2 = vertexs[indices[i + 2]].pos - vertexs[indices[i]].pos;
        glm::vec2 deltaUV1 = vertexs[indices[i + 1]].texCoord - vertexs[indices[i]].texCoord;
        glm::vec2 deltaUV2 = vertexs[indices[i + 2]].texCoord - vertexs[indices[i]].texCoord;

        glm::vec3 tangent1, bitangent1;
        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent1 = glm::normalize(tangent1);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent1 = glm::normalize(bitangent1);

        for (int j = 0;j < 3;j++)
        {
            if (vertexs[indices[i + j]].tangent == glm::vec3(0,0,0))
            {
                vertexs[indices[i + j]].tangent = tangent1;
                vertexs[indices[i + j]].binormal = bitangent1;
            }
            else
            {
                vertexs[indices[i + j]].tangent = glm::normalize(tangent1 + vertexs[indices[i + j]].tangent);
                vertexs[indices[i + j]].binormal = glm::normalize(bitangent1 + vertexs[indices[i + j]].binormal);
            }
        }
    }

	


}

void CreateTool::GetSphereData(std::vector<MyVertex>& vertexs, std::vector<uint16_t>& indices)
{
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            MyVertex temp;
            temp.pos = glm::vec3(xPos, yPos, zPos);
            temp.normal = glm::vec3(xPos, yPos, zPos);
            temp.texCoord = glm::vec2(xSegment, ySegment);
            vertexs.push_back(temp);
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
}