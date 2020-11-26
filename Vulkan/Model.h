#pragma once
#define TINYOBJLOADER_IMPLEMENTATION
#include <unordered_map>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "Configuration.h"
class Model
{
public:
	/*
	*ģ�͵�ַ
	*/
	std::string address;

	Model(std::string address);
	void LoadModel(std::vector<MyVertex>& vertices, std::vector<uint16_t>& indices);

};

