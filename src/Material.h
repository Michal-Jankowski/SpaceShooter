#pragma once
#include "ShaderProgram.h"
#include <assimp/material.h>
#include <map>

class Material 
{
public:
	Material(const float intensity, const float strength, const bool isEnabled = true);
    Material(const aiMaterial *assimpMat);
	static Material& none();
	void setUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
    void setup(const glm::mat4 model) const;
private:
	std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
	bool m_isEnabled;
	float m_specularIntensity;
	float m_specularStrength;

    std::string mainTextureKey;
    std::string shaderProgramKey;

    void generateMappings();
    std::map<std::string, std::string> materialShaderMappings;

    std::string loadMaterialTexture(const std::string &textureFileName);
    static std::string aiStringToStdString(const aiString& aiStringStruct);
};
