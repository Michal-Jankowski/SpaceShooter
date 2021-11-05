#version 440 core

layout(location = 0) out vec4 outputColour;

smooth in vec2 IOverTexCoord;
smooth in vec3 IOverNormal;

uniform sampler2D sampler;
uniform vec4 color;


struct AmbientLight {
    vec3 color;
    bool isOn;
};

vec3 getAmbientLightColour(AmbientLight ambientLight) {
    if(!ambientLight.isOn) { return vec3(0,0,0);}
    return ambientLight.color;
}

struct DiffuseLight {
    vec3 color;
    vec3 direction;
    float factor;
    bool isOn;
};

vec3 getDiffuseLightColour(DiffuseLight diffuseLight, vec3 normal) {
    if(!diffuseLight.isOn) { return vec3(0,0,0);}
    float finalIntensity = max(0.0, dot(normal, -diffuseLight.direction));
    finalIntensity = clamp(finalIntensity * diffuseLight.factor, 0.0, 1.0);
    return vec3(diffuseLight.color * finalIntensity);
}

uniform AmbientLight ambientLight;
uniform DiffuseLight diffuseLight;

void main() {
    vec3 normal = normalize(IOverNormal);
    vec4 texColor = texture(sampler, IOverTexCoord);
    vec4 objColor = texColor * color;
    vec3 lightColour = ambientLight.color + getDiffuseLightColour(diffuseLight, normal);
    outputColour =  objColor * vec4(lightColour, 1.0);
}