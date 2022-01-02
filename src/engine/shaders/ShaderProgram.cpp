#include "ShaderProgram.h"
ShaderProgram::~ShaderProgram() {
	deleteProgram();
}
void ShaderProgram::createProgram() {
	m_programID = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(const Shader& shShader) {
	if (!shShader.hasLoaded()) {
		return false;
	}
	glAttachShader(m_programID, shShader.getShaderID());
	return true;
}

bool ShaderProgram::linkProgram() {
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
 
void ShaderProgram::deleteProgram() {
	if (!m_programID == 0) {
		return;
	}
	std::cout << "Deleting shader program with ID " << m_programID << std::endl;
	m_isLinked = false;
	glDeleteProgram(m_programID);
}

void ShaderProgram::useProgram() const {
	if (m_isLinked) {
		glUseProgram(m_programID);
	}
}

unsigned ShaderProgram::getProgramID() const {
	return m_programID;
}

void ShaderProgram::setUniform(const std::string& sName, const int iValue) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform1iv(iLoc, 1, static_cast<const GLint*>(&iValue));
}


// Setting floats

void ShaderProgram::setUniform(const std::string& sName, float* fValues, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform1fv(iLoc, iCount, static_cast<const GLfloat*>(fValues));
}

void ShaderProgram::setUniform(const std::string& sName, const float fValue) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform1fv(iLoc, 1, static_cast<const GLfloat*>(&fValue));
}

// Setting vectors

void ShaderProgram::setUniform(const std::string& sName, glm::vec2* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform2fv(iLoc, iCount, reinterpret_cast<const GLfloat*>(vVectors));
}

void ShaderProgram::setUniform(const std::string& sName, const glm::vec2 vVector) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform2fv(iLoc, 1, reinterpret_cast<const GLfloat*>(&vVector));
}


void ShaderProgram::setUniform(const std::string& sName, glm::vec3* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform3fv(iLoc, iCount, reinterpret_cast<const GLfloat*>(vVectors));
}

void ShaderProgram::setUniform(const std::string& sName, const glm::vec3 vVector) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform3fv(iLoc, 1, reinterpret_cast<const GLfloat*>(&vVector));
}

void ShaderProgram::setUniform(const std::string& sName, glm::vec4* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform4fv(iLoc, iCount, reinterpret_cast<const GLfloat*>(vVectors));
}

void ShaderProgram::setUniform(const std::string& sName, const glm::vec4 vVector) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform4fv(iLoc, 1, reinterpret_cast<const GLfloat*>(&vVector));
}

// Setting 3x3 matrices

void ShaderProgram::setUniform(const std::string& sName, glm::mat3* mMatrices, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniformMatrix3fv(iLoc, iCount, false, reinterpret_cast<const GLfloat*>(mMatrices));
}

void ShaderProgram::setUniform(const std::string& sName, const glm::mat3 mMatrix) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniformMatrix3fv(iLoc, 1, false, reinterpret_cast<const GLfloat*>(&mMatrix));
}

// Setting 4x4 matrices

void ShaderProgram::setUniform(const std::string& sName, glm::mat4* mMatrices, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniformMatrix4fv(iLoc, iCount, false, reinterpret_cast<const GLfloat*>(mMatrices));
}

void ShaderProgram::setUniform(const std::string& sName, const glm::mat4 mMatrix) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniformMatrix4fv(iLoc, 1, false, reinterpret_cast<const GLfloat*>(&mMatrix));
}

// Setting integers

void ShaderProgram::setUniform(const std::string& sName, const int* iValues, int iCount) {
	int iLoc = glGetUniformLocation(m_programID, sName.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sName << " dose not exists or is not used, it will fail" << std::endl;
	}
	glUniform1iv(iLoc, iCount, reinterpret_cast<const GLint*>(iValues));
}



void ShaderProgram::SetModelAndNormalMatrix(const std::string& sModelMatrixName, const std::string& sNormalMatrixName, glm::mat4 mModelMatrix) {
	setUniform(sModelMatrixName, mModelMatrix);
	setUniform(sNormalMatrixName, glm::transpose(glm::inverse(glm::mat3(mModelMatrix))));
}

GLuint ShaderProgram::getUniformBlockIndex(const std::string& uniformBlockName) const {
	if (!m_isLinked) {
		std::cerr << "Cannot get index of uniform block " << uniformBlockName << " when program has not been linked!" << std::endl;
		return GL_INVALID_INDEX;
	}
	const auto result = glGetUniformBlockIndex(m_programID, uniformBlockName.c_str());
	if (result == GL_INVALID_INDEX) {
		std::cerr << "Could not get index of uniform block " << uniformBlockName << ", check if such uniform block really exists!" << std::endl;
	}
	return result;
}

void ShaderProgram::bindUniformBlockToBindingPoint(const std::string& uniformBlockName, GLuint bindingPoint) const {
	const auto blockIndex = getUniformBlockIndex(uniformBlockName);
	if (blockIndex != GL_INVALID_INDEX) {
		glUniformBlockBinding(m_programID, blockIndex, bindingPoint);
	}
}

void ShaderProgram::setTransformFeedbackRecordedVariables(const std::vector<std::string>& recordedVariablesNames, GLenum bufferMode) const {
	std::vector<const char*> recordedVariablesNamesPtrs;
	for (const auto& recordedVariableName : recordedVariablesNames) {
		recordedVariablesNamesPtrs.push_back(recordedVariableName.c_str());
	}

	glTransformFeedbackVaryings(m_programID, static_cast<GLsizei>(recordedVariablesNamesPtrs.size()), recordedVariablesNamesPtrs.data(), bufferMode);
}

