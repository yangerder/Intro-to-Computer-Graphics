#version 330 core

// TODO 2
// Implement Bling-Phong shading

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float gloss;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;
uniform sampler2D texture1;

in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    vec4 objColor = texture(texture1, texCoord);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 ambient = light.ambient * material.ambient * objColor.rgb;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse) * objColor.rgb;

    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.gloss);
    vec3 specular = light.specular * material.specular * spec ;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, objColor);
}