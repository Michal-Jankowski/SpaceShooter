#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, const float ambientFactor,
    const float constantAttenuation, const float linearAttenuation, const float exponentialAttenuation,
    const bool isOn)
    : position(position)
    , color(color)
    , ambientFactor(ambientFactor)
    , constantAttenuation(constantAttenuation)
    , linearAttenuation(linearAttenuation)
    , exponentialAttenuation(exponentialAttenuation)
    , isOn(isOn ? 1 : 0)
{
}

std::string PointLight::constructAttributeName(const std::string& uniformName, const std::string& attributeName)
{
    return uniformName + "." + attributeName;
}

void PointLight::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName)
{
    shaderProgram.setUniform(constructAttributeName(uniformName, "position"), position);
    shaderProgram.setUniform(constructAttributeName(uniformName, "color"), color);
    shaderProgram.setUniform(constructAttributeName(uniformName, "ambientFactor"), ambientFactor);
    shaderProgram.setUniform(constructAttributeName(uniformName, "constantAttenuation"), constantAttenuation);
    shaderProgram.setUniform(constructAttributeName(uniformName, "constantAttenuation"), constantAttenuation);
    shaderProgram.setUniform(constructAttributeName(uniformName, "exponentialAttenuation"), exponentialAttenuation);
    shaderProgram.setUniform(constructAttributeName(uniformName, "isOn"), isOn);
}

void* PointLight::getDataPointer() const {
    return (void*)&position;
}

GLsizeiptr PointLight::getDataSizeStd140() {
    // Here it's three times size of vec4 because:
    // - position + dummy padding make first vec4
    // - color + ambient factor make second vec4
    // - attenuation factors + isOn make third vec4
    return sizeof(glm::vec4) * 3;
}


PointLight& PointLight::none() {
    static PointLight nonePointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, false);
    return nonePointLight;
}
