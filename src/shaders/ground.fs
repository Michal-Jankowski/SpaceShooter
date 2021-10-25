#version 440 core

layout(location = 0) out vec4 outputColour;

smooth in vec2 vertexCoordsVS;

uniform sampler2D snowSampler;

void main()
{
    vec4 snowTexel = texture(snowSampler, vertexCoordsVS);
    outputColour = snowTexel;
}