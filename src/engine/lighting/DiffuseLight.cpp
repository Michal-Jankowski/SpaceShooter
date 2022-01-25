#include "DiffuseLight.h"
DiffuseLight::DiffuseLight(const glm::vec3& color, const glm::vec3& direction, const float factor)
    : m_color(color)
    , m_direction(direction)
    , m_factor(factor)
{
}

void DiffuseLight::setUniform(ShaderProgram& shaderProgram) {

    shaderProgram.setUniform("diffuseLight.color", m_color);
    shaderProgram.setUniform("diffuseLight.direction", m_direction);
    shaderProgram.setUniform("diffuseLight.factor", m_factor);
}
