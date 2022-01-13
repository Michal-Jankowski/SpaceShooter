#version 460 core

#include structs.incl
#include lighting.incl

layout(location = 0) out vec4 outputColour;

in VS_OUT{
    vec2 verTexCoord;
    vec3 verNormal;
    vec4 worldPosition;
    vec4 cameraSpacePosition;

    TangentSpace tangentSpace;
} fs_in;

uniform sampler2D diffTex;
uniform sampler2D normTex;
uniform vec4 color;
uniform vec3 cameraPosition;
uniform bool isStencil;

uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;
uniform PointLight pointLightOne, pointLightTwo;
uniform Material material;
uniform Laser laser;



void main() {

    vec4 texColor = texture(diffTex, fs_in.verTexCoord);

    if(texColor.a < 0.05) {
        discard;
    }
    vec3 normal = normalize(fs_in.verNormal);

    //texColor += texture(diffTex, IOVerTexCoord);

    vec4 objColor = texColor * color;

    vec3 ambient = getAmbientLightColour(ambientLight);
    vec3 lightColour = ambient;

    if(material.useNormalMap){
        vec3 normalMap = texture(normTex, fs_in.verTexCoord).rgb;
        normalMap = normalize(normalMap * 2.0 - 1.0);
        vec3 diff = getDiffuseLightColour(fs_in.tangentSpace.diffuseLight, normalMap);
        lightColour = lightColour + diff ;
    }
    else{
        vec3 diff = getDiffuseLightColour(diffuseLight, normal);
        lightColour = lightColour + diff ;
    }

    vec3 spec = getSpecularMaterialLightColour(diffuseLight, material, fs_in.worldPosition.xyz, normal, cameraPosition);
    lightColour = lightColour + spec;

    vec3 pointLightColourOne = getPointLightColour(pointLightOne, fs_in.worldPosition.xyz, normal);
    vec3 pointLightColourTwo = getPointLightColour(pointLightTwo, fs_in.worldPosition.xyz, normal);

    lightColour = lightColour + pointLightColourOne + pointLightColourTwo;

    if(laser.isOn) {
        outputColour = laser.color;
    } else {
        outputColour =  objColor * vec4(lightColour, 1.0);
        outputColour.xyz = fs_in.tangentSpace.diffuseLight.direction;
    }
    if(isStencil) {
        outputColour = color;
    }
}