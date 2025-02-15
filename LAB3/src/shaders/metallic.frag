#version 330 core

// TODO 5:
// Implement Metallic shading


struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform vec3 viewPos;
uniform sampler2D modelTexture;
uniform samplerCube skybox;

in vec2 texCoord;
in vec4 FragPos;
in vec3 Normal;

out vec4 FragColor;

const float bias = 0.2;
const float alpha = 0.4;
const float lightIntensity = 1.0;
void main() 
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos.xyz);
    vec3 viewDir = normalize(viewPos - FragPos.xyz);
    vec3 reflectDir =  -viewDir - 2 * dot(-viewDir, norm) * norm;

    vec3 reflectedColor = texture(skybox, reflectDir).rgb;
    vec3 modelColor = texture(modelTexture, texCoord).rgb;

    float lambertian = max(dot(lightDir, norm), 0.0); // L · N
    float B_d = lambertian * lightIntensity;
    float B = B_d + bias;

    vec3 diffuse_color = B * modelColor;

    vec3 final_color = alpha * diffuse_color + (1.0 - alpha) * reflectedColor;

    FragColor = vec4(final_color, 1.0);

}	
