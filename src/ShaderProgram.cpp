#include "ShaderProgram.h"
ShaderProgram::~ShaderProgram() {
	deleteProgram();
}
void ShaderProgram::createProgram()
{
	m_programID = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(const Shader& shShader)
{
	if (!shShader.hasLoaded()) {
		return false;
	}
	glAttachShader(m_programID, shShader.getShaderID());
	return true;
}

bool ShaderProgram::linkProgram()
{
	if (m_isLinked) {
		return true;
	}
	glLinkProgram(m_programID);
	int iLinkStatus;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &iLinkStatus);
	m_isLinked = iLinkStatus == GL_TRUE;
	if (!m_isLinked)
	{
		char infoLogBuffer[2048];
		int logLength;
		glGetProgramInfoLog(m_programID, 2048, &logLength, infoLogBuffer);

		std::cout << "Error! Shader program wasn't linked! The linker returned:\n\n " << infoLogBuffer << std::endl;

		return false;
	}

	return m_isLinked;
}    
 
void ShaderProgram::deleteProgram()
{
	if (!m_isLinked) {
		return;
	}
	m_isLinked = false;
	glDeleteProgram(m_programID);
}

void ShaderProgram::useProgram() const
{
	if (m_isLinked) {
		glUseProgram(m_programID);
	}
}

unsigned ShaderProgram::getProgramID() const
{
	return m_programID;
}

// Setting floats

void ShaderProgram::setUniform(std::string sName, float* fValues, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::setUniform(std::string sName, const float fValue)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::setUniform(std::string sName, glm::vec2* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec2 vVector)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(std::string sName, glm::vec3* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec3 vVector)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void ShaderProgram::setUniform(std::string sName, glm::vec4* vVectors, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void ShaderProgram::setUniform(std::string sName, const glm::vec4 vVector)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void ShaderProgram::setUniform(std::string sName, glm::mat3* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniformMatrix3fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(std::string sName, const glm::mat3 mMatrix)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniformMatrix3fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(std::string sName, glm::mat4* mMatrices, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniformMatrix4fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void ShaderProgram::setUniform(std::string sName, const glm::mat4 mMatrix)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniformMatrix4fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting integers

void ShaderProgram::setUniform(std::string sName, int* iValues, int iCount)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::setUniform(std::string sName, const int iValue)
{
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	glUniform1i(iLoc, iValue);
}

void ShaderProgram::SetModelAndNormalMatrix(std::string sModelMatrixName, std::string sNormalMatrixName, glm::mat4 mModelMatrix)
{
	setUniform(sModelMatrixName, mModelMatrix);
	setUniform(sNormalMatrixName, glm::transpose(glm::inverse(mModelMatrix)));
}
