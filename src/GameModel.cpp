//
// Created by aklin on 06.11.2021.
//

#include <glm/ext/matrix_transform.hpp>
#include "GameModel.h"
#include "ShaderProgramManager.h"

GameModel::GameModel(const std::string& path) {
    mModelMatrix = glm::mat4(1.0f);
    mesh.loadModelFromFile(path);
}

void GameModel::render() {
    mesh.render(mModelMatrix);
}

void GameModel::moveBy(glm::vec3 distance) {
    mModelMatrix = glm::translate(mModelMatrix, distance);
}

void GameModel::update(SetupWindow &gScene) {

}
