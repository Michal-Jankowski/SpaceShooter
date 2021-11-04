#include "DiffuseLight.h"
DiffuseLight::DiffuseLight(const glm::vec3& color, const glm::vec3& direction, const float factor, const bool isOn)
    : m_color(color)
    , m_direction(direction)
    , m_factor(factor)
    , m_isOn(isOn)
{
}
std::string DiffuseLight::constructAttributeName(const std::string& uniformName, const std::string& attributeName) {
    return uniformName + "." + attributeName;
}

void DiffuseLight::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName) {
    shaderProgram.setUniform(constructAttributeName(uniformName, "color"), m_color);
   // shaderProgram.setUniform(constructAttributeName(uniformName, "isOn"), m_isOn);
    shaderProgram.setUniform(constructAttributeName(uniformName, "direction"), m_direction);
    shaderProgram.setUniform(constructAttributeName(uniformName, "factor"), m_factor);
}

 DiffuseLight& DiffuseLight::none()
{
    static DiffuseLight noneDiffuseLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, false);
    return noneDiffuseLight;
}