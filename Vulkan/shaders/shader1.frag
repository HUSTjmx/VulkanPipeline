#version 450
#extension GL_ARB_separate_shader_objects : enable
#define LIGHT_NUM 1
#define PI 3.14159
#include"BRDF.cgnic"
layout(binding = 1) uniform Light {
    vec3 position;
    vec3 color;
    vec3 camPos;
} light_0;

layout(binding = 2) uniform sampler2D texSampler;
layout(binding = 3) uniform sampler2D normalSampler;

layout(location = 0) in vec3 worldPos;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragTangent;
layout(location = 4) in vec3 fragBinormal;

layout(location = 0) out vec4 outColor;

struct PointLight
{
    vec3 position;
    vec3 color;

}pointLight[LIGHT_NUM];

float Diffuse_Lambertian(vec3 N, vec3 L)
{
    return max(dot(N, L), 0.0);
}

float Specular_Phong(vec3 R, vec3 V, float sharpness)
{
    return pow(max(dot(R, V), 0.0), sharpness);
}

float Specular_Phong_H(vec3 N, vec3 H, float sharpness)
{
    return pow(max(dot(N, H), 0.0), sharpness);
}


vec3 BRDF_Phong(vec3 N, vec3 V, vec3 L, vec3 R, vec3 H, vec3 albedo, vec3 F0)
{
    float dif = Diffuse_Lambertian(N, L);
    float spec = Specular_Phong(R, V, 16) ;
    vec3 F = Fresnel_Schlick(F0, N, L);

    return dif * albedo * (1 - F0)  + spec * F0 ; 
}

vec3 BRDF_Cook_Torrance(vec3 N, vec3 V, vec3 L, vec3 R, vec3 H, vec3 albedo, vec3 F0, float roughness, float metallic)
{
    float NDF = GGX_NDF(N, H, roughness);
    float Lambda_L = GGX_Lambda(N, V, roughness);
    float Lambda_V = GGX_Lambda(N, L, roughness);
    float G = Smith_G2_AngleAndHeight(N, V, L, Lambda_V, Lambda_L, 0);
    vec3 F = Fresnel_Schlick(F0, N, L);

    vec3 nominator = NDF * G * F;
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;

    vec3 spec = nominator / denominator;
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    float N_L = max(dot(N, L), 0.0);
    return (kD * albedo / PI + kS * spec) * N_L;
}

void main() {

    vec3 ambient = vec3(0.05, 0.05, 0.05);
    vec3 albedo =  pow(texture(texSampler, fragTexCoord).rgb, vec3(2.2));
    //vec3 albedo =  vec3(0.5,0.5,0.7);
    vec3 F0 = vec3(0.5, 0.6, 0.8);
    float metallic  = 0.7;
    float roughness = 0.3;

    F0 = mix(F0, albedo, metallic);

    mat3 TBN = transpose(mat3(fragTangent,fragBinormal,fragNormal));

    vec3 N = texture(normalSampler,fragTexCoord).rgb;
    N = normalize(N * 2.0 - 1.0);
    vec3 V = TBN*normalize(light_0.camPos - worldPos);
    vec3 L = TBN*normalize(light_0.position - worldPos);
    vec3 R = normalize(reflect(-L, N));
    vec3 H = normalize(L + V);

    vec3 brdf = BRDF_Cook_Torrance(N, V, L, R, H, albedo, F0, roughness, metallic);
    //brdf = BRDF_Phong(N, V, L, R, H, albedo, F0);
    vec3 color = brdf * light_0.color;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1/2.2));
    outColor = vec4(color, 1);
 //   outColor = vec4(dot(R, V),dot(R, V),dot(R, V), 1);
}