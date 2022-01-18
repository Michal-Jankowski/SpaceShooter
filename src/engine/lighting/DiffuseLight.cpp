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

void DiffuseLight::switchLight(ShaderProgram& shaderProgram, const bool enable)  {
    shaderProgram.setUniform(constructAttributeName("diffuseLight", "isDiffuseOn"), enable);
    m_isOn = enable;
}

bool DiffuseLight::getLightState() const {
    return m_isOn;
}

void DiffuseLight::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName) {
    shaderProgram.setUniform(constructAttributeName(uniformName, "color"), m_color);
    shaderProgram.setUniform(constructAttributeName(uniformName, "isDiffuseOn"), m_isOn);
    shaderProgram.setUniform(constructAttributeName(uniformName, "direction"), m_direction);
    shaderProgram.setUniform(constructAttributeName(uniformName, "factor"), m_factor);
}

 DiffuseLight& DiffuseLight::none()
{
    static DiffuseLight noneDiffuseLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, false);
    return noneDiffuseLight;
}