#include "ShaderProgramManager.h"
#include <stdexcept>

ShaderProgramManager& ShaderProgramManager::getInstance() {
    static ShaderProgramManager shaderProgramManager;
    return shaderProgramManager;
}

ShaderProgram& ShaderProgramManager::createShaderProgram(const std::string& key) {
    if (containsShaderProgram(key)) {
        auto msg = "Shader program with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->createProgram();
    m_shaderProgramKeys[key] = std::move(shaderProgram);

    return getShaderProgram(key);
}

ShaderProgram& ShaderProgramManager::getShaderProgram(const std::string& key) const {
    if (!containsShaderProgram(key))
    {
        auto msg = "Attempting to get non-existing shader program with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *m_shaderProgramKeys.at(key);
}

void ShaderProgramManager::linkAllPrograms() {
    for (const auto& keyShaderProgramPair : m_shaderProgramKeys) {
        if (!keyShaderProgramPair.second->linkProgram()) {
            auto msg = "Could not link shader program with key '" + keyShaderProgramPair.first + "'!";
            throw std::runtime_error(msg.c_str());
        }
    }
}

void ShaderProgramManager::clearShaderProgramCache() {
    m_shaderProgramKeys.clear();
}

bool ShaderProgramManager::containsShaderProgram(const std::string& key) const {
    return m_shaderProgramKeys.count(key) > 0;
}