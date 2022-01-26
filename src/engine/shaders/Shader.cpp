#include "Shader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../utils/Shadinclude.hpp"

Shader::~Shader() {
    deleteShader();
}

bool Shader::loadShaderFromFile(const std::string& file, GLenum shaderType) {
    std::vector<std::string> shaderLines;

#ifdef _DEBUG
    shaderSource = Shadinclude::load(file);
#else
    std::string shaderSource = Shadinclude::load(file);
#endif
    if(shaderSource.empty()){
        return false;
    }
    m_shaderID = glCreateShader(shaderType);
    const char *c_str = shaderSource.c_str();

    glShaderSource(m_shaderID, 1, &c_str, nullptr);
    glCompileShader(m_shaderID);

    int compilationStatus;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compilationStatus);

    if (compilationStatus == GL_FALSE) {
        char shaderLogBuffer[2048];
        int logLength;
        glGetShaderInfoLog(m_shaderID, 2048, &logLength, shaderLogBuffer);
        std::cout << "Error! Shader file " << file << "failed to compile! Info from shader: " << shaderLogBuffer << std::endl;
        return false;
    }
    this->m_shaderType = shaderType;
    m_hasLoaded = true;

    return true;
}

bool Shader::hasLoaded() const {
    return m_hasLoaded;
}

GLuint Shader::getShaderID() const {
    return m_shaderID;
}

GLenum Shader::getShaderType() const {
    return m_shaderType;
}

void Shader::deleteShader() {
    if (!m_hasLoaded) {
        return;
    }
    std::cout << "Deleting shader with ID " << m_shaderID << std::endl;
    m_hasLoaded = false;
    glDeleteShader(m_shaderID);
}