#version 440 core

uniform struct
{
   mat4 projectionMatrix;
   mat4 viewMatrix;
   mat4 modelMatrix;
} matrices;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

smooth out vec2 vertexTexCoordsVS;

void main()
{
    mat4 MVP_Matrix = matrices.projectionMatrix * matrices.viewMatrix * matrices.modelMatrix;
    gl_Position = MVP_Matrix * vec4(vertexPosition, 1.0);
    vertexTexCoordsVS = vertexTexCoords;
}