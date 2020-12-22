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
	ģ�͵�ַ
	*/
	std::string address;
	/*
	ģ��Ŀ¼
	*/
	string directory;
	/*
	�Ƿ�٤��У��
	*/
	bool gammaCorrection;
	/*
	�����ߴ�
	*/
	float scaleSize;
	/*
	ģ��ê�����������
	*/
	glm::vec3 originPosition;
	/*
	ͼ���������
	*/
	TextureImage* textureImages[IMAGE_NUM];


	/*
	 comment: ���캯��1��ģ����������Ĭ��Ϊ��ģ�͵�Ĭ��ê��λ��Ϊ(0,0,0)
	 */
	Model(std::string address);

	/*
	 comment: ���캯��2������ģ���������ӣ�ģ�͵�Ĭ��ê��λ��Ϊ(0,0,0)
	 */
	Model(std::string address, float size);

	/*
	 comment: ���캯��3������ģ���������ӣ�����ê��λ��
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

