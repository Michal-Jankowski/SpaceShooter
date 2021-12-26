#version 440 core

//#include "src/shaders/pointLight.frag"

layout(location = 0) out vec4 outputColour;

smooth in vec2 IOVerTexCoord;
smooth in vec3 IOVerNormal;
smooth in vec4 IOWorldPosition;
smooth in vec4 IOCameraSpacePosition;
uniform sampler2D sampler;
uniform vec4 color;
uniform vec3 cameraPosition;

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

struct PointLight
{
	vec3 position;
	vec3 color;
	
	float ambientFactor;

	float constantAttenuation;
	float linearAttenuation;
	float exponentialAttenuation;
	
	bool isOn;
};


uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;
uniform Material material;

uniform int numPointLights;
layout(std140, binding = 1) uniform pointLightBlock
{
    PointLight lights[5];
} pointLights_block;

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

vec3 getPointLightColor(const PointLight pointLight, const vec3 worldPosition, const vec3 normal)
{
	if(!pointLight.isOn) {
		return vec3(0.0);
	}
	
	vec3 positionToLightVector = worldPosition - pointLight.position;
	float distance = length(positionToLightVector);
	positionToLightVector = normalize(positionToLightVector);
	
	float diffuseFactor = max(0.0, dot(normal, -positionToLightVector));	
	float totalAttenuation = pointLight.constantAttenuation
		+ pointLight.linearAttenuation * distance
		+ pointLight.exponentialAttenuation * pow(distance, 2.0);

	return pointLight.color * (pointLight.ambientFactor + diffuseFactor) / totalAttenuation;
}


void main() {
   vec3 normal = normalize(IOVerNormal);
    vec4 texColor = texture(sampler, IOVerTexCoord);
    if(texColor.a < 0.05)
        discard;
    vec4 objColor = texColor * color;
    vec3 ambientColour = getAmbientLightColour(ambientLight);
    vec3 diffuseColour = getDiffuseLightColour(diffuseLight, normal);
    vec3 specularColour = getSpecularMaterialLightColour(diffuseLight, material, IOWorldPosition.xyz, normal, cameraPosition);
    vec3 lightColour = ambientColour + diffuseColour + specularColour;
    for(int i = 0; i < numPointLights; ++i) {
            vec3 pointLightColour = getPointLightColor(pointLights_block.lights[i], IOWorldPosition.xyz, normal);
            lightColour += pointLightColour;
    }
    outputColour =  objColor * vec4(lightColour, 1.0);
}