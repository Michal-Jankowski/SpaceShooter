#pragma once
#include "glm/glm.hpp"
#include <string>
#include "ShaderProgram.h"
class AmbientLight
{
public:
	AmbientLight(const glm::vec3& color, const bool isOn = true);
	void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
	glm::vec3 getColorContribution() const;
private:
	std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
	glm::vec3 m_color; 
	bool m_isOn; 

};

