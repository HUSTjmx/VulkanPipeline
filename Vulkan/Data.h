#ifndef Data_H_
#define Data_H_   

#include <vulkan/vulkan.h>

#define GLEW_STATIC
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<array>
#include<vector>
#include<string>
#include"Configuration.h"

const std::vector<MyVertex> vertices2 = {
    {{-0.5f, -1.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -1.5f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 1.5f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 1.5f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<VectorIndexType> indices2 = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
};

const std::vector<MyVertex> vertices1 = {
// positions          // normals           // texture coords
{{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f} },
{{   0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f,  0.0f} },
{{  0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f }},
{{    0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f }},
{{    -0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  1.0f }},
{{   -0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f }},

{ {    -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f }},
{ {     0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  0.0f }},
{ {     0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f }},
{ {     0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f }},
{ {    -0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f,  1.0f }},
{ {    -0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f,  0.0f }},

{ {    -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  0.0f }},
{ {    -0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  1.0f }},
{ {    -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  1.0f }},
{ {    -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  1.0f }},
{ {    -0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  0.0f }},
{ {    -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  0.0f }},

{ {     0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f }},
{ {    0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  1.0f }},
{ {     0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f }},
{ {   0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f }},
{ {     0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f }},
{ {   0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f }},

{ {    -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, { 0.0f,  1.0f }},
{ {     0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  1.0f }},
{ {     0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f }},
{ {     0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f }},
{ {    -0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f,  0.0f }},
{ {    -0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f,  1.0f }},

{ {    -0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f }},
{ {     0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  1.0f }},
{ {     0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f }},
{ {     0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f }},
{ {    -0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  0.0f }},
{ {    -0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f }}
};

//const std::vector<VectorIndexType> indices = {
//0, 1, 2, 0, 2, 3,    // front
//0, 3, 4, 0, 4, 5,    // right
//0, 5, 6, 0, 6, 1,    // up
//1, 6, 7, 1, 7, 2,    // left
//7, 4, 3, 7, 3, 2,    // down
//4, 7, 6, 4, 6, 5     // back
//};

//模型1的顶点和索引数组
std::vector<MyVertex> model_vertices_1;
std::vector<VectorIndexType> model_indices_1;


#endif