#version 330 core

in vec2 texCoord;
in vec3 Normal;

uniform sampler2D texture_diffuse0;

out vec4 FragColor;
uniform vec4 color;

void main()
{
	FragColor = texture(texture_diffuse0, texCoord);
}