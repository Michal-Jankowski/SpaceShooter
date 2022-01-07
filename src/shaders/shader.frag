#version 440 core

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

struct Laser {
    vec4 color;
    bool isOn;
};

struct AmbientLight {
    vec3 color;
    bool isOn;
};

struct DiffuseLight {
    vec3 color;
    vec3 direction;
    float factor;
    bool isOn;
};

struct Material {
    bool isOn;
    float specularIntensity;
    float specularStrength;
};

uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;
uniform Material material;
uniform Laser laser;

vec3 getAmbientLightColour(AmbientLight ambientLight) {
    if(!ambientLight.isOn) { return vec3(0.0);}
    return ambientLight.color;
}

vec3 getDiffuseLightColour(DiffuseLight diffuseLight, vec3 normal) {
    if(!diffuseLight.isOn) { return vec3(0.0);}
    float lightIntensity = max(0.0, dot(normal, -diffuseLight.direction));
    lightIntensity = clamp(lightIntensity * diffuseLight.factor, 0.0, 1.0);
    vec3 intensityByColor = diffuseLight.color * lightIntensity;
    return intensityByColor;
}

vec3 getSpecularMaterialLightColour(DiffuseLight diffuseLight, Material material, vec3 worldPosition, vec3 normal, vec3 cameraPosition) {
    
    if(!material.isOn) {
    return vec3(0.0);
    }
    vec3 reflectedVector = normalize(reflect(diffuseLight.direction, normal));
    vec3 worldTocameraVector = normalize(cameraPosition - worldPosition);
    float specularThreshold = dot(worldTocameraVector, reflectedVector);
    if(specularThreshold > 0) {
        specularThreshold = pow(specularThreshold, material.specularStrength);
        return diffuseLight.color * material.specularIntensity * specularThreshold;
    }
    return vec3(0.0);
}

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