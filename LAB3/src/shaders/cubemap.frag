#version 330 core

// TODO 4-1
// Implement CubeMap shading

in vec3 TexCoords;

uniform samplerCube skybox;

out vec4 FragColor;

void main()
{
    FragColor = texture(skybox, TexCoords);
}