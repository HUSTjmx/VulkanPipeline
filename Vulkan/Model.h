#pragma once
#define TINYOBJLOADER_IMPLEMENTATION
#include <unordered_map>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "Configuration.h"
#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "TextureImage.h"

using namespace std;

class Model
{
public:
	/*
	模型地址
	*/
	std::string address;
	/*
	模型目录
	*/
	string directory;
	/*
	是否伽马校正
	*/
	bool gammaCorrection;
	/*
	缩减尺寸
	*/
	float scaleSize;
	/*
	模型锚点的世界坐标
	*/
	glm::vec3 originPosition;
	/*
	图像纹理对象
	*/
	TextureImage* textureImages[IMAGE_NUM];


	/*
	 comment: 构造函数1，模型缩放因子默认为，模型的默认锚点位置为(0,0,0)
	 */
	Model(std::string address);

	/*
	 comment: 构造函数2，传入模型缩放因子，模型的默认锚点位置为(0,0,0)
	 */
	Model(std::string address, float size);

	/*
	 comment: 构造函数3，传入模型缩放因子，传入锚点位置
	 */
	Model(std::string address, float size, glm::vec3 position);

	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void LoadModel2(std::vector<MyVertex>& vertices, std::vector<uint16_t>& indices);

	void LoadModel2(std::vector<MyVertex>& vertices, std::vector<uint32_t>& indices);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene, std::vector<MyVertex>& vertices, std::vector<uint16_t>& indices);

	void processNode(aiNode* node, const aiScene* scene, std::vector<MyVertex>& vertices, std::vector<uint32_t>& indices);

    void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<MyVertex>& vertices, std::vector<uint16_t>& indices);

	void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<MyVertex>& vertices, std::vector<uint32_t>& indices);
   
	void LoadModel(std::vector<MyVertex>& vertices, std::vector<uint16_t>& indices);

	void LoadModel(std::vector<MyVertex>& vertices, std::vector<uint32_t>& indices);

	void InitTextures(std::array<std::string, IMAGE_NUM + 10> ImageAddressArray, CommandBuffer* commandBuffer);

	void DestroyTextures();
};

