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

smooth out vec2 IOverTexCoord;
smooth out vec3 IOverNormal;

void main() {

	mat4 MVP_matrix = matrices.projectionMatrix * matrices.viewMatrix * matrices.modelMatrix;
	IOverTexCoord = verTexCoord;
	IOverNormal = matrices.normalMatrix * verNormal;
	gl_Position = MVP_matrix * vec4(verTexPos, 1.0);

}