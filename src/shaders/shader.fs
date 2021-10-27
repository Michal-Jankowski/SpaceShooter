#version 440 core

layout(location = 0) out vec4 outputColour;

smooth in vec2 verTexCoord;

uniform sampler2D sampler;
uniform vec4 color;

void main()
{
    vec4 texColor = texture(sampler, verTexCoord);
    outputColour = texColor * color;
}