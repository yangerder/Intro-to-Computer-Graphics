#version 330 core

// TODO 6-1:
// Implement Glass-Schlick shading

struct Light {
    vec3 position;
};


uniform Light light;
uniform vec3 viewPos;
uniform samplerCube skybox;

in vec4 FragPos;
in vec3 Normal;

out vec4 FragColor;

const float airRefractiveIndex = 1.0;
const float glassRefractiveIndex = 1.52;

vec3 calculateRefractDir(vec3 I, vec3 N, float eta) {
    float cosThetaI = dot(-I, N);
    float sin2ThetaI = 1.0 - cosThetaI * cosThetaI;
    float sin2ThetaT = eta * eta * sin2ThetaI;

    if (sin2ThetaT > 1.0) {
        return vec3(0.0);
    }

    float cosThetaT = sqrt(1.0 - sin2ThetaT);
    return eta * I + (eta * cosThetaI - cosThetaT) * N;
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos.xyz);

    // Schlick Approximation
    float n1 = airRefractiveIndex;
    float n2 = glassRefractiveIndex;
    float R0 = pow((n1 - n2) / (n1 + n2), 2.0);
    float cosTheta = dot(-viewDir, norm);
    float fresnel = R0 + (1.0 - R0) * pow((1.0 + cosTheta), 5.0);

    vec3 reflectDir = -viewDir - 2 * dot(-viewDir, norm) * norm;
    vec3 refractDir = calculateRefractDir(-viewDir, norm, n1 / n2);

    vec3 reflectedColor = texture(skybox, reflectDir).rgb;
    vec3 refractedColor = texture(skybox, refractDir).rgb;
    

    vec3 finalColor = (1.0 - fresnel) *refractedColor  + fresnel * reflectedColor;
    FragColor = vec4(finalColor, 1.0);
}