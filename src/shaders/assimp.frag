#version 460 core

#include structs.incl
#include lighting.incl

layout(location = 0) out vec4 outputColour;

in VS_OUT{
    vec2 verTexCoord;
    vec3 verNormal;
    vec4 worldPosition;
    vec4 cameraSpacePosition;
    vec3 tangentSpaceLightDir;
} fs_in;

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

    vec4 texColor = texture(diffTex, fs_in.verTexCoord);

    if(texColor.a < 0.05) {
        discard;
    }
    vec3 normal = normalize(fs_in.verNormal);
    //vec3 normal = texture(normTex, fs_in.verTexCoord).rgb;
    //normal = normalize(normal * 2.0 - 1.0);
    //normal = normalize(fs_in.TBN * normal);
    //texColor += texture(diffTex, IOVerTexCoord);

    vec4 objColor = texColor * color;
    vec3 lightColour = getAmbientLightColour(ambientLight) +
                       getDiffuseLightColour(diffuseLight, normal) +
                       getSpecularMaterialLightColour(diffuseLight,
                                                      material,
                                                      fs_in.worldPosition.xyz,
                                                      normal,
                                                      cameraPosition);

    if(laser.isOn) {
        outputColour = laser.color;
    } else {
        outputColour =  objColor * vec4(lightColour, 1.0);
    }
    if(isStencil) {
        outputColour = color;
    }
}