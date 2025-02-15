#version 330 core
out vec4 FragColor;

in vec2 TexCoord; 

uniform sampler2D ourTexture;
uniform vec3 rainbowColor;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    vec3 finalColor = texColor.rgb * rainbowColor;
    FragColor = vec4(finalColor,texColor.a);
}