#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>

    class PointLight
    {
    public:
        PointLight(const glm::vec3& position, const glm::vec3& color, const float ambientFactor,
            const float constantAttenuation, const float linearAttenuation, const float exponentialAttenuation);
       void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
       std::string concatenateUniformStruct(const std::string& uniformName, const std::string& attributeName);
    private:
        glm::vec3 position; 
        glm::vec3 m_color; 
        float m_ambientFactor;
        float m_constantAttenuation; 
        float m_linearAttenuation; 
        float m_exponentialAttenuation; 
    };
