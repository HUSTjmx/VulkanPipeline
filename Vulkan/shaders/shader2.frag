#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform Light {
    vec3 position;
    vec3 color;
} light_0;

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 ambient=vec3(0.1f,0.1f,0.1f);

void main() {
    
    outColor = texture(texSampler, fragTexCoord);
}