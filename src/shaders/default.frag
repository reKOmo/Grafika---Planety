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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse0, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse0, texCoord));
    vec3 specular = light.specular * spec * specularColor;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main()
{
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = 0.1  * vec3(texture(texture_diffuse0, texCoord));
    // phase 2: Point lights
    for(int i = 0; i < totalPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}