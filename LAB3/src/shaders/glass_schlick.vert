#version 330 core

// TODO 6-1:
// Implement Glass-Schlick shading

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 FragPos;
out vec3 Normal;

void main() 
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = model * vec4(aPos, 1.0f); 
    Normal = mat3(transpose(inverse(model))) * aNormal; 
}