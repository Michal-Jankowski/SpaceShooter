#version 460 core

uniform struct
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
} matrices;

layout(location = 0) in vec3 verTexPos;
out vec3 texCoords;

void main() 
{
	texCoords = verTexPos;
	mat4 MV_Matrix = matrices.viewMatrix * matrices.modelMatrix;
	mat4 MVP_matrix = matrices.projectionMatrix * MV_Matrix;
	vec4 position = MVP_matrix * vec4(verTexPos, 1.0);
	gl_Position = position.xyww;
}