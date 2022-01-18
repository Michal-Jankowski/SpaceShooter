#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm/glm.hpp>

    class PointLight
    {
    public:
        PointLight(const glm::vec3& position, const glm::vec3& color, const float ambientFactor,
            const float constantAttenuation, const float linearAttenuation, const float exponentialAttenuation,
            const bool isOn = true);
        void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
        static GLsizeiptr getDataSizeStd140();
        void* getDataPointer() const;
        std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
        static PointLight& none();
    private:
        glm::vec3 position; 
        float padding{ 0 };
        glm::vec3 color; 
        float ambientFactor;
        float constantAttenuation; 
        float linearAttenuation; 
        float exponentialAttenuation; 
        bool isOn; 
    };
