#version 460 core

#include structs.incl
#include lighting.incl

layout(location = 0) out vec4 outputColour;

smooth in vec2 IOVerTexCoord;
smooth in vec3 IOVerNormal;
smooth in vec4 IOWorldPosition;
smooth in vec4 IOCameraSpacePosition;
uniform sampler2D diffTex;
uniform sampler2D normTex;
uniform vec4 color;
uniform vec3 cameraPosition;
uniform bool isStencil;

uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;
uniform Material material;
uniform Laser laser;

void main() {
    //vec3 normal = normalize(IOVerNormal);
    vec3 normal = texture(normTex, IOVerTexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    vec4 texColor = texture(diffTex, IOVerTexCoord);
    //texColor += texture(diffTex, IOVerTexCoord);
    if(texColor.a < 0.05) {
        discard;
    }
    vec4 objColor = texColor * color;
    vec3 lightColour = getAmbientLightColour(ambientLight) + getDiffuseLightColour(diffuseLight, normal)
    + getSpecularMaterialLightColour(diffuseLight, material, IOWorldPosition.xyz, normal, cameraPosition);
    if(laser.isOn) {
        outputColour = laser.color;
    } else {
        outputColour =  objColor * vec4(lightColour, 1.0);
    }
    if(isStencil) {
        outputColour = color;
    }
}