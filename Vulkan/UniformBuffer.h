#pragma once
#ifndef UNIFORMBUFFER
#define UNIFORMBUFFER

#include"MyBuffer.h"
#include"Camera.h""
#include"Configuration.h"
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

class UniformBuffer:MyBuffer{
public:
	std::vector<VkBuffer> selfs;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDeviceSize bufferSize;

    UniformBuffer(SwapChain* swapChain, VkDeviceSize bufferSize);

    void createUniformBuffers(SwapChain* swapChain);

    void updateUniformBuffer(uint32_t currentImage, SwapChain* swapChain,Camera* camera);

    void updateLightBuffer(uint32_t currentImage, SwapChain* swapChain, glm::vec3 camPos);

    void updateObjectPosition(uint32_t currentImage, SwapChain* swapChain, glm::vec3 objectPosition);

    void updateCameraPosition(uint32_t currentImage, SwapChain* swapChain, glm::vec3 camPosition);

    void Destroy(SwapChain* swapChain, VkDevice device);

private:
    VertexOfUniformBufferObject vertexShaderUniform{};
    FragmentOfUniformBufferObject fragmentShaderUNiform{};
};
#endif // !UNIFORMBUFFER