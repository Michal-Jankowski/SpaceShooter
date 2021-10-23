#pragma once
#include "..\src\Shader.h"
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

	// Setting vectors
	void setUniform(std::string sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec2 vVector);
	void setUniform(std::string sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec3 vVector);
	void setUniform(std::string sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(std::string sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(std::string sName, float* fValues, int iCount = 1);
	void setUniform(std::string sName, const float fValue);

	// Setting 3x3 matrices
	void setUniform(std::string sName, glm::mat3* mMatrices, int iCount = 1);
	void setUniform(std::string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void setUniform(std::string sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(std::string sName, const glm::mat4 mMatrix);

	// Setting integers
	void setUniform(std::string sName, int* iValues, int iCount = 1);
	void setUniform(std::string sName, const int iValue);

	// Model and normal matrix setting ispretty common
	void SetModelAndNormalMatrix(std::string sModelMatrixName, std::string sNormalMatrixName, glm::mat4 mModelMatrix);

private:
	GLuint m_programID; // ID of program
	bool m_isLinked = false; // Whether program was linked and is ready to use
};
