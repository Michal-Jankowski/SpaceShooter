#include "AmbientLight.h"

AmbientLight::AmbientLight(const glm::vec3& color, const bool isOn)
    : m_color(color)
    , m_isOn(isOn)
{
}

void AmbientLight::switchLight(ShaderProgram& shaderProgram, const bool enable) {
    shaderProgram.setUniform("ambientLight.isAmbientOn", enable);
    m_isOn = enable;
}

bool AmbientLight::isLightEnabled() const {
    return m_isOn;
}

void AmbientLight::setUniform(ShaderProgram& shaderProgram) {
    shaderProgram.setUniform("ambientLight.color", m_color);
    shaderProgram.setUniform("ambientLight.isAmbientOn", m_isOn);
}

