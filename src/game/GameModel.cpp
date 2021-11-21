//
// Created by aklin on 06.11.2021.
//

#include <glm/ext/matrix_transform.hpp>
#include "GameModel.h"
#include "../ShaderProgramManager.h"

GameModel::GameModel(const std::string& path) {
    mModelMatrix = glm::mat4(1.0f);
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

}

void GameModel::onCollision(GameModel *other) {
    std::cout << "colliding" << std::endl;
}

glm::vec3 GameModel::getPosition() {
    return glm::vec3(mModelMatrix[0][3], mModelMatrix[1][3], mModelMatrix[2][3]);
}
