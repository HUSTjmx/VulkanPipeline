#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec3 inBinormal;

layout(location = 0) out vec3 worldPos;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragTangent;
layout(location = 4) out vec3 fragBinormal;

void main() {
   // gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    float a = 1000.0f;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition/a, 1.0);
    worldPos = vec3(ubo.model * vec4(inPosition/a, 1.0));

    fragNormal = normalize(mat3(transpose(inverse(ubo.model))) * inNormal);  
    fragTangent = normalize(mat3(transpose(inverse(ubo.model))) * inTangent);
    fragBinormal = normalize(mat3(transpose(inverse(ubo.model))) * inBinormal);

    fragTexCoord = inTexCoord;
}

// #version 450
// #extension GL_ARB_separate_shader_objects : enable

// layout(binding = 0) uniform UniformBufferObject {
//     mat4 model;
//     mat4 view;
//     mat4 proj;
// } ubo;

// layout(location = 0) in vec3 inPosition;
// layout(location = 1) in vec3 inColor;
// layout(location = 2) in vec2 inTexCoord;

// layout(location = 0) out vec3 fragColor;
// layout(location = 1) out vec2 fragTexCoord;

// void main() {
//     gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
//     fragColor = inColor;
//     fragTexCoord = inTexCoord;
// }