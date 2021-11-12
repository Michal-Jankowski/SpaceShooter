#pragma once
#include "ShaderProgram.h"

class Material 
{
public:
	Material(const float intensity, const float strength, const bool isEnabled = true);
	static Material& none();
	void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
private:
	std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
	bool m_isEnabled;
	float m_specularIntensity;
	float m_specularStrength;
};

