#version 440 core

uniform struct
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	mat3 normalMatrix;
} matrices;

layout(location = 0) in vec3 verTexPos;
layout(location = 1) in vec2 verTexCoord;
layout(location = 2) in vec3 verNormal;

smooth out vec2 IOVerTexCoord;
smooth out vec3 IOVerNormal;
smooth out vec4 IOWorldPosition;
smooth out vec4 IOCameraSpacePosition;

void main() 
{
	mat4 MV_Matrix = matrices.viewMatrix * matrices.modelMatrix;
	mat4 MVP_matrix = matrices.projectionMatrix * MV_Matrix;
	IOVerTexCoord = verTexCoord;
	IOVerNormal = matrices.normalMatrix * verNormal;
	IOWorldPosition = matrices.modelMatrix * vec4(verTexPos, 1.0);
	IOCameraSpacePosition = MV_Matrix * vec4(verTexPos, 1.0);

	gl_Position = MVP_matrix * vec4(verTexPos, 1.0);
}