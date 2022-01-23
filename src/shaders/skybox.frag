#version 460 core

layout(location = 0) out vec4 outputColour;

in vec3 texCoords;
uniform samplerCube skybox;

void main()
{
	outputColour = texture(skybox, texCoords);
}