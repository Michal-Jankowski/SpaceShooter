#pragma once

#include "Shader.h"
#include <string>
#include <map>
#include <memory>

class ShaderManager
{
public:
	static ShaderManager& getInstance();

	void loadVertexShader(const std::string& key, const std::string& path);
	const Shader& getVertexShader(const std::string& key) const;
	void loadFragmentShader(const std::string& key, const std::string& pasth);
	const Shader& getFragmentShader(const std::string& key) const;
	void clearShaderCache();
private:
	ShaderManager() {}
	ShaderManager(const ShaderManager&) = delete;
	void operator=(const ShaderManager&) = delete;
	bool hasVertexShader(const std::string& key) const;
	bool haasFragmentShader(const std::string& key) const;

	std::map<std::string, std::unique_ptr<Shader>> m_vertexShaderKeys; 
	std::map<std::string, std::unique_ptr<Shader>> m_fragmentShaderKeys;

};

