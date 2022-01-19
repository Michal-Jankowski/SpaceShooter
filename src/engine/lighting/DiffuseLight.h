#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>

class DiffuseLight
{
public:
    DiffuseLight(const glm::vec3& color, const glm::vec3& direction, const float factor);
    void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
    static DiffuseLight& none();
private:
    std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
    glm::vec3 m_color; 
    glm::vec3 m_direction; 
    float m_factor; 
};

