#version 440 core

out vec4 outputColor;

smooth in vec2 IOVerTexCoord;
smooth in vec3 IOVerNormal;
smooth in vec4 IOWorldPosition;
smooth in vec4 IOCameraSpacePosition;

void main()
{
    outputColor = vec4(0.04, 0.28, 0.26, 1.0);
}