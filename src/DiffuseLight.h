#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class DiffuseLight
{
public:
    DiffuseLight(const glm::vec3& color, const glm::vec3& direction, const float factor, const bool isOn = true);
    void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
    void switchLight(ShaderProgram& shaderProgram, const bool enable);
    bool getLightState() const;
    static DiffuseLight& none();
private:
    std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
    glm::vec3 m_color; 
    glm::vec3 m_direction; 
    float m_factor; 
    bool m_isOn;
};

