#version 440 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec3 vertexNormal;

out vec3 IOVertexPosition;
out vec3 IOVertexNormal;

void main()
{
    IOVertexPosition = vertexPosition;
    IOVertexNormal = vertexNormal;
}