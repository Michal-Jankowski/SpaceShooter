#version 460 core

uniform struct
{
	mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 modelMatrix;
} matrices;

layout(location = 0) in vec3 verTexPos;

void main()
{
    mat4 MV_Matrix = matrices.viewMatrix * matrices.modelMatrix;
	mat4 MVP_matrix = matrices.projectionMatrix * MV_Matrix;
    gl_Position = MVP_matrix * vec4(verTexPos, 1.0);
}