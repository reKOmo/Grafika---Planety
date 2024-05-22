#version 330 core

in vec2 texCoord;
in vec3 Normal;

uniform sampler2D texture_diffuse0;

out vec4 FragColor;
uniform vec4 color;

void main()
{
	vec4 diffuse = texture(texture_diffuse0, texCoord);
	float gamma = 2.2;
    FragColor = vec4(pow(diffuse.rgb, vec3(1.0/gamma)), diffuse.a);
}