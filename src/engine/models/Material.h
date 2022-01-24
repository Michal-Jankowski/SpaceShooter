#pragma once
#include "../shaders/ShaderProgram.h"
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
    [[nodiscard]] const bool isTransparent();
private:
	std::string constructAttributeName(const std::string& uniformName, const std::string& attributeName);
	bool m_isEnabled;
	float m_specularIntensity;
	float m_specularStrength;
	bool m_isTransparent;

    std::string mainTextureKey;
    bool hasNormal = false;
    std::string normalTextureKey;
    static const std::string assimpModelsShaderKey;

    std::string loadMaterialTexture(const std::string &textureFileName);
    static std::string aiStringToStdString(const aiString& aiStringStruct);
};
