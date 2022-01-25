#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>

class DiffuseLight
{
public:
    DiffuseLight(const glm::vec3& color, const glm::vec3& direction, const float factor);
    void setUniform(ShaderProgram& shaderProgram);
private:
    glm::vec3 m_color; 
    glm::vec3 m_direction; 
    float m_factor; 
};

