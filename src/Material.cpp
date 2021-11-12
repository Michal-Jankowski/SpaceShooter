#include "Material.h"

Material::Material(const float intensity, const float strength, const bool isEnabled)
    : m_specularIntensity(intensity)
    , m_specularStrength(strength)
    , m_isEnabled(isEnabled)
{
}

Material& Material::none() {
    static Material noMaterial(0.0f, 0.0f, false);
    return noMaterial;
}

void Material::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName) {
    shaderProgram.setUniform(constructAttributeName(uniformName, "isOn"), m_isEnabled);
    if (!m_isEnabled) {
        return;
    }
    shaderProgram.setUniform(constructAttributeName(uniformName, "specularIntensity"), m_specularIntensity);
    shaderProgram.setUniform(constructAttributeName(uniformName, "specularStrength"), m_specularStrength);
}

std::string Material::constructAttributeName(const std::string& uniformName, const std::string& attributeName) {
    return uniformName + "." + attributeName;
}
