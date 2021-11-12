//
// Created by aklin on 06.11.2021.
//

#include "GameModel.h"
#include "ShaderProgramManager.h"

GameModel::GameModel(const std::string& path, const std::string& shaderKey) {
    mModelMatrix = glm::mat4(1.0f);
    mesh.loadModelFromFile(path);
    //mesh
    auto& shaderProgramManager = ShaderProgramManager::getInstance();
    shaderProgramManager.createOrGetShaderProgram(shaderKey);
}

void GameModel::render() {

}
