
#include "GameModel.h"

GameModel::GameModel(const std::string& path, glm::vec3 position) {

    mesh.loadModelFromFile(path);
    transform = std::make_unique<Transform>();
    transform->setPosition(position);
}

void GameModel::render() {
    mesh.render(transform->getMatrix());
}






