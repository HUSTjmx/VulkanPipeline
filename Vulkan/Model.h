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

using namespace std;

class Model
{
public:
	/*
	*Ä£ÐÍµØÖ·
	*/
	std::string address;
	string directory;
	bool gammaCorrection;

	Model(std::string address);
    
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
};

