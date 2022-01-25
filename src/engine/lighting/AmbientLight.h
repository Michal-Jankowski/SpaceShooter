#pragma once
#include "glm/glm.hpp"
#include <string>
#include "../shaders/ShaderProgram.h"
class AmbientLight
{
public:
	AmbientLight(const glm::vec3& color, const bool isOn = true);
	void setUniform(ShaderProgram& shaderProgram);
	void switchLight(ShaderProgram& shaderProgram, const bool enable);
	bool isLightEnabled() const;
	glm::vec3 m_color;
	bool m_isOn;
private:	

};

