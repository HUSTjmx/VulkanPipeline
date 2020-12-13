#pragma once

#include <vulkan/vulkan.h>

#define GLEW_STATIC
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <vector>
#include <optional>
#include <iostream>
#include <set>
#include<array>

#define UNIFORM_NUM 2


//视窗大小
const uint32_t WIDTH = 1200;
const uint32_t HEIGHT = 800;

//顶点着色器、片元着色器的相对地址
const std::string VertAddr = "shaders/vert.spv";
const std::string FragAddr = "shaders/frag1.spv";

//最大的运行帧数
const int MAX_FRAMES_IN_FLIGHT = 2;


/********验证层相关********/
const std::vector<const char*> validationLayers = {
"VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


/********设备扩展相关********/
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


/********交换链属性相关********/
struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};



/********队列族相关********/
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() {
        return graphicsFamily.has_value() & presentFamily.has_value();
    }
};

struct MyVertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent = glm::vec3(0, 0, 0);
    glm::vec3 binormal = glm::vec3(0, 0, 0);
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(MyVertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 5> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 5> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(MyVertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(MyVertex, normal);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(MyVertex, texCoord);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(MyVertex, tangent);

        attributeDescriptions[4].binding = 0;
        attributeDescriptions[4].location = 4;
        attributeDescriptions[4].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[4].offset = offsetof(MyVertex, binormal);

        return attributeDescriptions;
    }

    bool operator==(const MyVertex& other) const {
        return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
    }
};


struct CameraOfUniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct PointLightOfUniformBufferObject {
    alignas(16) glm::vec3 Position;
    alignas(16) glm::vec3 Color;
    alignas(16) glm::vec3 CamPos;
};


#define IMAGE_NUM  2
#define UNIFORM_NUM 2
#define MODEL_NUM 1
const std::array<std::string, IMAGE_NUM + 10> ImageAddressArray =
{
    "textures/KHTK/T1_C.jpg",
    "textures/KHTK/T1_N.jpg",
    "textures/Circuitry/Circuitry Emission.png"
};

/********模型相关********/
const std::array<std::string, MODEL_NUM> ModelAddress = {
     "models/KHTK/KHTK_mesh.obj",

};

//索引类型
#define ModelIndexType VK_INDEX_TYPE_UINT32

#define VectorIndexType uint32_t

const std::array<std::string, MODEL_NUM + 100> temp = {
    "models/Man1/body_dif.png",
    "models/Man1/nanosuit.obj",

    "models/room/room.obj",

    "models/stand/Arma.obj",
    "models/stand/block.obj",
    "models/stand/Buddha.obj",
    "models/stand/bunny.obj",
    "models/stand/cube.obj",
    "models/stand/dinosaur.obj",
    "models/stand/dragon.obj",
    "models/stand/fandisk.obj",
    "models/stand/horse.obj",
    "models/stand/kitten.obj",
    "models/stand/rocker.obj",
    "models/stand/sphere.obj",
    
    "models/KHTK/KHTK_mesh.obj",


    "textures/Circuitry/Circuitry Albedo.png",
    "textures/Circuitry/Circuitry Normals.png",
    "textures/Circuitry/Circuitry Emission.png",

    "textures/Lava/Lava Albedo Smoothness.png",
    "textures/Lava/Lava Emission.png",
    "textures/Lava/Lava Normals.png",

    "textures/KHTK/T1_C.jpg",
    "textures/KHTK/T1_AO.jpg",
    "textures/KHTK/T1_E.png",
    "textures/KHTK/T1_M.png",
    "textures/KHTK/T1_N.jpg",
    "textures/KHTK/T1_R.jpg"

};

