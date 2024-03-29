#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <iostream>
class ShaderProgram
{
public:
	void createProgram();
	~ShaderProgram();
	void deleteProgram();
	bool addShaderToProgram(const Shader& shShader);
	bool linkProgram();
	void useProgram() const;

	GLuint getProgramID() const;
	// Setting integers
	void setUniform(const std::string& sName, const int* iValues, int iCount);
	void setUniform(const std::string& sName, const int iValue);
	// Setting vectors
	void setUniform(const std::string& sName, glm::vec2* vVectors, int iCount);
	void setUniform(const std::string& sName, const glm::vec2 vVector);
	void setUniform(const std::string& sName, glm::vec3* vVectors, int iCount);
	void setUniform(const std::string& sName, const glm::vec3 vVector);
	void setUniform(const std::string& sName, glm::vec4* vVectors, int iCount);
	void setUniform(const std::string& sName, const glm::vec4 vVector);
	// Setting floats
	void setUniform(const std::string& sName, float* fValues, int iCount);
	void setUniform(const std::string& sName, const float fValue);
	// Setting 3x3 matrices
	void setUniform(const std::string& sName, glm::mat3* mMatrices, int iCount);
	void setUniform(const std::string& sName, const glm::mat3 mMatrix);
	// Setting 4x4 matrices
	void setUniform(const std::string&  sName, glm::mat4* mMatrices, int iCount);
	void setUniform(const std::string&  sName, const glm::mat4 mMatrix);
	void SetModelAndNormalMatrix(const std::string& sModelMatrixName, const std::string& sNormalMatrixName, glm::mat4 mModelMatrix);

private:
	GLuint m_programID;
	bool m_isLinked = false;
#ifdef _DEBUG
	std::vector<std::string> shaderSources;
#endif
};
