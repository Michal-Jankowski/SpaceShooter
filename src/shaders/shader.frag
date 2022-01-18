#version 460 core

#include structs.incl
#include lighting.incl

layout(location = 0) out vec4 outputColour;

smooth in vec2 IOVerTexCoord;
smooth in vec3 IOVerNormal;
smooth in vec4 IOWorldPosition;
smooth in vec4 IOCameraSpacePosition;
uniform sampler2D diffTex;
uniform vec4 color;
uniform vec3 cameraPosition;
uniform bool isStencil;

uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;
uniform PointLight pointLightOne, pointLightTwo;
uniform Material material;
uniform Laser laser;

void main() {
    vec3 normal = normalize(IOVerNormal);
    vec4 texColor = texture(diffTex, IOVerTexCoord);
    if(texColor.a < 0.05) {
        discard;
    }
    vec4 objColor = texColor * color;
    vec3 lightColour = getAmbientLightColour(ambientLight) + getDiffuseLightColour(diffuseLight, normal)
    + getSpecularMaterialLightColour(diffuseLight, material, IOWorldPosition.xyz, normal, cameraPosition);
    vec3 pointLightColourOne = getPointLightColour(pointLightOne, IOWorldPosition.xyz, normal);
    vec3 pointLightColourTwo = getPointLightColour(pointLightTwo, IOWorldPosition.xyz, normal);
    lightColour += pointLightColourOne + pointLightColourTwo;
    if(laser.isLaserOn) {
        outputColour = laser.color;
    } else {
        outputColour =  objColor * vec4(lightColour, 1.0);
    }
    if(isStencil) {
        outputColour = color;
    }
}