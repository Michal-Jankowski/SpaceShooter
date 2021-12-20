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


layout(location = 0) in vec3 vertexPosition;

void main()
{
  mat4 MV_Matrix = matrices.viewMatrix * matrices.modelMatrix;
  mat4 MVP_matrix = matrices.projectionMatrix * MV_Matrix;
  gl_Position = MVP_matrix * vec4(verTexPos, 1.0);
}