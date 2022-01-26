#include "PointLight.h"

    PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, const float ambientFactor,
        const float constantAttenuation, const float linearAttenuation, const float exponentialAttenuation)
        : position(position)
        , m_color(color)
        , m_ambientFactor(ambientFactor)
        , m_constantAttenuation(constantAttenuation)
        , m_linearAttenuation(linearAttenuation)
        , m_exponentialAttenuation(exponentialAttenuation)
    {
    }
    
    std::string PointLight::concatenateUniformStruct(const std::string& uniformName, const std::string& attributeName) {
        return uniformName + "." + attributeName;
    }

    void PointLight::setUniform(ShaderProgram& shaderProgram, const std::string& uniformName)
    {
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "position"), position);
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "color"), m_color);
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "ambientFactor"), m_ambientFactor);
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "constantAttenuation"), m_constantAttenuation);
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "linearAttenuation"), m_linearAttenuation);
        shaderProgram.setUniform(concatenateUniformStruct(uniformName, "exponentialAttenuation"), m_exponentialAttenuation);
    }

void PointLight::setPosition(const glm::vec3 &pos) {
    position = pos;
}
