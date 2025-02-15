#version 330 core

// TODO 3:
// Implement Gouraud shading

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float gloss;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 ambientColor;
out vec4 diffuseColor;
out vec4 specularColor;
out vec2 texCoord;

void main()
{
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vec3 Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflect = normalize(reflect(-lightDir, Normal));

    vec3 ambient = light.ambient * material.ambient;
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    float spec = pow(max(dot(reflect, viewDir), 0.0), material.gloss);
    vec3 specular = light.specular * material.specular * spec;

    ambientColor = vec4(ambient, 1.0);
    diffuseColor = vec4(diffuse, 1.0);
    specularColor = vec4(specular, 1.0);

    texCoord = aTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}