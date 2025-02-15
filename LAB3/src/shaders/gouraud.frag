#version 330 core

// TODO 3:
// Implement Gouraud shading

uniform sampler2D texture1;

in vec4 ambientColor;
in vec4 diffuseColor;
in vec4 specularColor;

in vec2 texCoord;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(texture1, texCoord);

    FragColor = ambientColor * texColor + diffuseColor * texColor + specularColor;
}