//
// Created by aklin on 06.11.2021.
//

#include <glm/ext/matrix_transform.hpp>
#include "GameModel.h"
#include "../ShaderProgramManager.h"

GameModel::GameModel(const std::string& path, glm::vec3 pos) {
    mModelMatrix = glm::translate(glm::mat4(1.0f), pos);
    mesh.loadModelFromFile(path);
}

void GameModel::render() {
    mesh.render(mModelMatrix);
    if(useCollision){
        col->drawDebug();
    }
}

void GameModel::moveBy(glm::vec3 distance) {
    mModelMatrix = glm::translate(mModelMatrix, distance);
}

void GameModel::update(SetupWindow &gScene) {
    if (col) {
        col->pos = getPosition();
    }
}

void GameModel::onCollision(GameModel *other) {
    //std::cout << "colliding" << std::endl;
}

glm::vec3 GameModel::getPosition() {
    return glm::vec3(mModelMatrix[3][0], mModelMatrix[3][1], mModelMatrix[3][2]);
}
