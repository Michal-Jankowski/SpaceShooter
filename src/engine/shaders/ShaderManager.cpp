#include "ShaderManager.h"
#include <stdexcept>
ShaderManager& ShaderManager::getInstance() {
    static ShaderManager shaderManager;
    return shaderManager;
}

void ShaderManager::loadVertexShader(const std::string& key, const std::string& filePath) {
    if (containsVertexShader(key)) {
        auto msg = "Vertex shader with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto vertexShader = std::make_unique<Shader>();
    if (!vertexShader->loadShaderFromFile(filePath, GL_VERTEX_SHADER)) {
        auto msg = "Could not load vertex shader '" + filePath + "'!";
        throw std::runtime_error(msg);
    }

   m_vertexShaderKeys[key] = std::move(vertexShader);
}

void ShaderManager::loadFragmentShader(const std::string& key, const std::string& filePath) {
    if (containsFragmentShader(key)) {
        auto msg = "Fragment shader with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto fragmentShader = std::make_unique<Shader>();
    if (!fragmentShader->loadShaderFromFile(filePath, GL_FRAGMENT_SHADER)) {
        auto msg = "Could not load fragment shader '" + filePath + "'!";
        throw std::runtime_error(msg);
    }

    m_fragmentShaderKeys[key] = std::move(fragmentShader);
}

const Shader& ShaderManager::getVertexShader(const std::string& key) const {
    if (!containsVertexShader(key)) {
        auto msg = "Attempting to get non-existing vertex shader with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *m_vertexShaderKeys.at(key);
}

const Shader& ShaderManager::getFragmentShader(const std::string& key) const {
    if (!containsFragmentShader(key)) {
        auto msg = "Attempting to get non-existing fragment shader with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *m_fragmentShaderKeys.at(key);
}

bool ShaderManager::containsVertexShader(const std::string& key) const {
    return m_vertexShaderKeys.count(key) > 0;
}

bool ShaderManager::containsFragmentShader(const std::string& key) const {
    return m_fragmentShaderKeys.count(key) > 0;
}

void ShaderManager::clearShaderCache() {
    m_vertexShaderKeys.clear();
    m_fragmentShaderKeys.clear();
}
