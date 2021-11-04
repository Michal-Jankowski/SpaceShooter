#include "AmbientLight.h"

AmbientLight::AmbientLight(const glm::vec3& color, const bool isOn)
    : m_color(color)
    , m_isOn(isOn)
{
}

std::string AmbientLight::constructAttributeName(const std::string& uniformName, const std::string& attributeName) {
    return uniformName + "." + attributeName;
}

void AmbientLight::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName) {
    shaderProgram.setUniform(constructAttributeName(uniformName, "color"), m_color);
    //shaderProgram.setUniform(constructAttributeName(uniformName, "isOn"), m_isOn);
}

glm::vec3 AmbientLight::getColorContribution() const {
    return m_isOn ? m_color : glm::vec3(0.0f);
}