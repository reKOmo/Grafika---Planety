#version 330 core
#define MAX_POINT_LIGHTS 128

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform vec3 viewPos;

uniform sampler2D texture_diffuse0;

uniform vec3 ambientColor;
uniform vec3 color;
uniform float shininess;
uniform float shineStrength;
uniform vec3 specularColor;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int totalPointLights;

float gt(float val, float m) {
    if (val > m)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir   = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    //float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess) * diff;
    float spec = max(dot(halfwayDir, normal), 0.0f);
    spec = pow(spec, shininess) * diff;

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
    
    // combine results
    vec3 ambient  = light.ambient * vec3(texture(texture_diffuse0, texCoord));
    vec3 diffuse  = light.diffuse * vec3(texture(texture_diffuse0, texCoord)) * diff;
    vec3 specular = light.specular * specularColor * spec * shineStrength;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 gammaCorrection (vec3 colour, float gamma) {
  return pow(colour, vec3(1. / gamma));
}

void main()
{
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec4 textureDiffuseColor = texture(texture_diffuse0, texCoord);
    // small ambient
    vec3 result = 0.01  * vec3(textureDiffuseColor);

    // phase 2: Point lights
    for(int i = 0; i < totalPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    
    float gamma = 2.2;
    FragColor = vec4(gammaCorrection(result, gamma), textureDiffuseColor.a);
    //FragColor = vec4(result, textureDiffuseColor.a);
}