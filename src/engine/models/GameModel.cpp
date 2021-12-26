
#include "GameModel.h"

GameModel::GameModel(const std::string& path) {

    mesh.loadModelFromFile(path);
    transform = std::make_shared<Transform>();
}

void GameModel::render() {
    mesh.render(transform->getMatrix());
}






