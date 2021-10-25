#version 440 core

uniform struct
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
} matrices;

layout(location = 0) in vec3 verTexPos;
layout(location = 1) in vec2 inVerTexCoord;

smooth out vec2 verTexCoord;

void main() {
	mat4 MVP_matrix = matrices.projectionMatrix * matrices.viewMatrix * matrices.modelMatrix;
	gl_Position = MVP_matrix * vec4(verTexPos, 1.0);
	verTexCoord = inVerTexCoord;
}