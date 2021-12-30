#pragma once
#include "ShaderProgram.h"
#include <map>

class ShaderProgramManager
{
public:
	static ShaderProgramManager& getInstance();

	ShaderProgram& createShaderProgram(const std::string& key);
	ShaderProgram& getShaderProgram(const std::string& key) const;
	ShaderProgram& createOrGetShaderProgram(const std::string& key);
	void linkAllPrograms();
	void clearShaderProgramCache();
private:
	ShaderProgramManager() {} 
	ShaderProgramManager(const ShaderProgramManager&) = delete; 
	void operator=(const ShaderProgramManager&) = delete; 

	bool containsShaderProgram(const std::string& key) const;

	std::map<std::string, std::unique_ptr<ShaderProgram>> m_shaderProgramKeys; 

};

