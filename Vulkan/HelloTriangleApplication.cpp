#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//�Զ�����
#include"ValidationLayer.h"
#include"FrameBuffer.h"
#include"DescriptorSets.h"
#include"VertexBuffer.h"
#include"TextureImage.h"
#include"DepthImage.h"
#include"Camera.h"
#include"Data.h"
#include"Model.h"
//���
Camera* camera;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

 // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

class HelloTriangleApplication {
public:
    GLFWwindow* window;
    VkInstance instance;
    //���Իص���Ϣ
    ValidationLayer* validationLayer;
    //�����豸
    PhysicalDevice* physicalDevice;
    //�߼��豸
    LogicDevice* logicDevice;
    //���ڱ���
    VkSurfaceKHR surface;
    //�����������
    SwapChain* swapChain;
    //ͼ�ιܵ�(���� Render Pass)
    GraphicsPipeline* graphicsPipeline;
    //FrameBuffers
    FrameBuffer* frameBuffer;
    //�������
    CommandBuffer* commandBuffer;
    //���㻺����
    VertexBuffer* verterBuffer;
    //��Ķ��㻺����
    VertexBuffer* vertexBufferForSphere;

    //���������Ĳ���
    DescriptorSetLayout* descriptorSetLayout;
    //ȫ�ֱ���uniform����������MVP
    UniformBuffer* uniformBuffer;
    //uniform����������PointLight
    UniformBuffer* LightUniBuffer;
    //��������
    DescriptorSets* descriptorSets;
    //��Ȼ�����Դ
    DepthImage* depthImage;

    //ģ������
    std::vector<Model*> Models;
    //ģ�͵Ķ�������
    std::vector<std::vector<MyVertex>> Models_Vertex;
    //ģ�͵���������
    std::vector<std::vector<VectorIndexType>> Models_indices;
    //�������黺��������
    std::vector<VertexBuffer*> Models_Vertex_Buffers;

    void run() {
        initWindow();
        initVulkan();

        camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f));
        for (int i = 0;i < swapChain->swapChainImages.size();i++)
        {
            LightUniBuffer->updateLightBuffer(i, swapChain, camera->Position);
        }

        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }

    void initVulkan() {
        createInstance();

        validationLayer = new ValidationLayer(instance);

        createSurface();

        physicalDevice = new PhysicalDevice(instance,surface);

        logicDevice = new LogicDevice(physicalDevice->self, surface);

        swapChain = new SwapChain(logicDevice,physicalDevice,window);

        descriptorSetLayout = new DescriptorSetLayout(logicDevice->self);
        
        graphicsPipeline = new GraphicsPipeline(swapChain,descriptorSetLayout);

        commandBuffer = new CommandBuffer(physicalDevice, graphicsPipeline);
        commandBuffer->createCommandPool();


        depthImage = new DepthImage();
        depthImage->commandBuffer = commandBuffer;
        depthImage->createDepthResources();

        frameBuffer = new FrameBuffer(*swapChain, *graphicsPipeline,depthImage->self_view);

        LoadModels();

        InitVertexBuffers();

       // std::vector<MyVertex> sphere_vertexs;
       // std::vector<uint32_t>sphere_indices;
       // CreateTool::GetSphereData(sphere_vertexs, sphere_indices);
       //// CreateTool::SetTangentAndBiForVertex(sphere_vertexs, sphere_indices);
       // vertexBufferForSphere = new VertexBuffer(swapChain, sphere_vertexs, sphere_indices);
       // vertexBufferForSphere->createSelf(commandBuffer->commandPool);
       // vertexBufferForSphere->createIndexBuffer(commandBuffer->commandPool);
       // Models_Vertex_Buffers.push_back(vertexBufferForSphere);

        //printf_s("bbb: %d %d\n", Models_Vertex_Buffers[0]->indices_32.size(), Models_Vertex_Buffers[0]->vertices.size());

        uniformBuffer = new UniformBuffer(swapChain, sizeof(VertexOfUniformBufferObject));
        uniformBuffer->createUniformBuffers(swapChain);

        LightUniBuffer = new UniformBuffer(swapChain, sizeof(FragmentOfUniformBufferObject));
        LightUniBuffer->createUniformBuffers(swapChain);

        descriptorSets = new DescriptorSets();
        descriptorSets->createDescriptorPool(swapChain);
        descriptorSets->createSelf(swapChain, descriptorSetLayout, uniformBuffer, textureImages ,LightUniBuffer);
        
        commandBuffer->Create(frameBuffer->swapChainFramebuffers);
        commandBuffer->excuteCommandBufferForAll(frameBuffer->swapChainFramebuffers, Models_Vertex_Buffers, descriptorSets->self);
        commandBuffer->createSyncObjects();
    }

    void createInstance()
    {
        //��֤��������ж�
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        //Ҫ����ʵ�����������ȱ����ڽṹ�����һЩ�й�����Ӧ�ó������Ϣ�����Ż����ǵ�Ӧ�ó���
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //Vulkan���кܶ���Ϣ��ͨ���ṹ�崫�ݵģ�������ͨ�������������ݵģ����Ǳ��������һ���ṹ�壬�Ա�Ϊ����ʵ���ṩ�㹻����Ϣ��
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        //ָ�������ȫ����չ
        //GLFW��һ����������ú���������������Ҫ����չ��
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        //ȫ����֤�������
        ValidationLayer* VLayer = new ValidationLayer();
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            //����(��֤��)���
            VLayer->populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        //����ʵ���Ƿ�ɹ�
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }


    }

    void mainLoop() {
        //ҪʹӦ�ó���һֱ���У�ֱ�����ִ����رմ��ڣ�������Ҫ��mainLoop�������һ���¼�ѭ����������ʾ
        while (!glfwWindowShouldClose(window)) {
            // per-frame time logic
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(logicDevice->self);
    }

    //������SwapChain��ص���Դ
    //Problem:command�ڴ�ز���Ҫ���٣���������д����������
    void cleanupSwapChain()
    {
        depthImage->DestroyAll();

        frameBuffer->Destroy();

        commandBuffer->DestroySelf();

        graphicsPipeline->Destroy();

        swapChain->Destroy(logicDevice->self);

        commandBuffer->DestroyOthers();

        uniformBuffer->Destroy(swapChain, logicDevice->self);

        LightUniBuffer->Destroy(swapChain, logicDevice->self);

        descriptorSets->destroyDescriptorPool(logicDevice);
    }

    //����������Ҫ�ͷŵ���Դ
    void cleanup() {
        cleanupSwapChain();

        DestroyImages();

        descriptorSetLayout->DestroySelf(logicDevice->self);

        DestroyVertexBuffers();

        logicDevice->Destroy();

        validationLayer->cleanUp();

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    //����ƽ��
    void createSurface()
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface");
        }
    }

    //�ؽ�SwapChain����ض���
    void reCreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(logicDevice->self);

        cleanupSwapChain();

        swapChain = new SwapChain(logicDevice, physicalDevice, window);
        //swapChain->ReCreate();

        graphicsPipeline = new GraphicsPipeline(swapChain,descriptorSetLayout);

        commandBuffer = new CommandBuffer(physicalDevice, graphicsPipeline);
        commandBuffer->createCommandPool();

        depthImage = new DepthImage();
        depthImage->commandBuffer = commandBuffer;
        depthImage->createDepthResources();

        frameBuffer = new FrameBuffer(*swapChain, *graphicsPipeline, depthImage->self_view);

        uniformBuffer = new UniformBuffer(swapChain, sizeof(VertexOfUniformBufferObject));
        uniformBuffer->createUniformBuffers(swapChain);

        LightUniBuffer = new UniformBuffer(swapChain, sizeof(FragmentOfUniformBufferObject));
        LightUniBuffer->createUniformBuffers(swapChain);

        descriptorSets = new DescriptorSets();
        descriptorSets->createDescriptorPool(swapChain);
        descriptorSets->createSelf(swapChain, descriptorSetLayout, uniformBuffer,textureImages,LightUniBuffer);

        commandBuffer->Create(frameBuffer->swapChainFramebuffers);
        //commandBuffer->excuteCommandBufferForAll(frameBuffer->swapChainFramebuffers, Models_Vertex_Buffers, descriptorSets->self);
        commandBuffer->excuteCommandBufferByIndex(frameBuffer->swapChainFramebuffers, Models_Vertex_Buffers[0], descriptorSets->self);
        commandBuffer->createSyncObjects();

        for (int i = 0;i < swapChain->swapChainImages.size();i++)
        {
            LightUniBuffer->updateLightBuffer(i, swapChain,camera->Position);
        }
    }

    //����FrameBuffer
    void drawFrame() {
        vkWaitForFences(logicDevice->self, 1, &commandBuffer->inFlightFences[frameBuffer->currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;

        VkResult result = vkAcquireNextImageKHR(logicDevice->self, swapChain->self, UINT64_MAX, commandBuffer->imageAvailableSemaphores[frameBuffer->currentFrame], VK_NULL_HANDLE, &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR)
        {
            reCreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        uniformBuffer->updateUniformBuffer(imageIndex, swapChain, camera);
        LightUniBuffer->updateCameraPosition(imageIndex, swapChain, camera->Position);


        // Check if a previous frame is using this image (i.e. there is its fence to wait on)
        if (commandBuffer->imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(logicDevice->self, 1, &commandBuffer->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        // Mark the image as now being in use by this frame
        commandBuffer->imagesInFlight[imageIndex] = commandBuffer->inFlightFences[frameBuffer->currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore waitSemaphores[] = { commandBuffer->imageAvailableSemaphores[frameBuffer->currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer->commandBuffers[imageIndex];
        VkSemaphore signalSemaphores[] = { commandBuffer->renderFinishedSemaphores[frameBuffer->currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(logicDevice->self, 1, &commandBuffer->inFlightFences[frameBuffer->currentFrame]);
        if (vkQueueSubmit(logicDevice->graphicsQueue, 1, &submitInfo, commandBuffer->inFlightFences[frameBuffer->currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }
        

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = { swapChain->self };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;
        result = vkQueuePresentKHR(logicDevice->presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || frameBuffer->framebufferResized) {
            frameBuffer->framebufferResized = false;
            reCreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        frameBuffer->UpdateCurrentFrame();
  
    }

    //�������¶����С֮��Ļص�
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
        app->frameBuffer->framebufferResized = true;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->ProcessKeyboard(RIGHT, deltaTime);

    }
    
    void DestroyImages()
    {
        for (int i = 0;i < IMAGE_NUM;i++)
        {
            Models[i]->DestroyTextures();
        }
    }

    /*
    *comment������ģ��
    */
    void LoadModels()
    {
        for (int i = 0;i < MODEL_NUM;i++)
        {
            Model* temp = new Model(ModelAddress[i], ModelScaleFactor[i], ModelOriginPosition[i]);
            std::vector<MyVertex> temp1;
            Models_Vertex.push_back(temp1);
            std::vector<VectorIndexType> temp2;
            Models_indices.push_back(temp2);
            temp->LoadModel2(Models_Vertex[i], Models_indices[i]);

            temp->InitTextures(ImageAddressArray, commandBuffer);
            Models.push_back(temp);
        }
    }

    /*
    *comment���������㻺��������
    */
    void InitVertexBuffers()
    {
        for (int i = 0;i < MODEL_NUM;i++)
        {
            VertexBuffer* temp  = new VertexBuffer(swapChain, Models_Vertex[i], Models_indices[i]);
            temp->createSelf(commandBuffer->commandPool);
            temp->createIndexBuffer(commandBuffer->commandPool);
            Models_Vertex_Buffers.push_back(temp);

        }
    }

    /*
    *comment�����ٶ��㻺��������
    */
    void DestroyVertexBuffers()
    {
        for (int i = 0;i < MODEL_NUM;i++)
        {
            Models_Vertex_Buffers[i]->DestroyAll();
        }
    }

};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}