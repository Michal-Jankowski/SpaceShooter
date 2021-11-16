#pragma once
#include <GLAD/glad.h>
#include <string>
#include <vector>

class Shader
{
public:
	~Shader();
	bool loadShaderFromFile(const std::string& file, GLenum shaderType);
	bool hasLoaded() const;
	GLuint getShaderID() const;
	GLenum getShaderType() const;
	void deleteShader();
private:
	bool getLinesFromFile(const std::string& fileName, std::vector<std::string>& result, bool isReadingIncludedFile = false) const;
	GLuint m_shaderID = 0;
	GLenum m_shaderType = 0;
	bool m_hasLoaded = false;
};

