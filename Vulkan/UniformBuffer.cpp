#include"UniformBuffer.h"
#include <ctime>


UniformBuffer::UniformBuffer(SwapChain* swapChain, VkDeviceSize bufferSize)
{
    this->bufferSize = bufferSize;
    this->swapChain = swapChain;

}

void UniformBuffer::createUniformBuffers(SwapChain* swapChain) {
    selfs.resize(swapChain->swapChainImages.size());
    uniformBuffersMemory.resize(swapChain->swapChainImages.size());

    for (size_t i = 0; i < swapChain->swapChainImages.size(); i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, selfs[i], uniformBuffersMemory[i]);
    }
}

void UniformBuffer::updateUniformBuffer(uint32_t currentImage, SwapChain* swapChain,Camera* camera) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    CameraOfUniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = camera->GetViewMatrix();
    ubo.proj = glm::perspective(glm::radians(camera->Zoom), swapChain->swapChainExtent.width / (float)swapChain->swapChainExtent.height, 0.1f, 50.0f);

    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(swapChain->logicDevice->self, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(swapChain->logicDevice->self, uniformBuffersMemory[currentImage]);
}

void UniformBuffer::updateLightBuffer(uint32_t currentImage, SwapChain* swapChain, glm::vec3 camPos)
{

    PointLightOfUniformBufferObject light{};
    light.Position = glm::vec3(0.0f, 0.0f, 3.0f);
    light.Color = glm::vec3(1.0, 1.0, 1.0f);
    light.CamPos = camPos;

  
    //printf_s("%f,%f,%f\n", light.CamPos.x, light.CamPos.y, light.CamPos.z);
    void* data;
    vkMapMemory(swapChain->logicDevice->self, uniformBuffersMemory[currentImage], 0, sizeof(light), 0, &data);
    memcpy(data, &light, sizeof(light));
    vkUnmapMemory(swapChain->logicDevice->self, uniformBuffersMemory[currentImage]);
}

void UniformBuffer::Destroy(SwapChain* swapChain, VkDevice device)
{
    for (size_t i = 0; i < swapChain->swapChainImages.size(); i++) {
        vkDestroyBuffer(device, selfs[i], nullptr);
        vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
    }
}
