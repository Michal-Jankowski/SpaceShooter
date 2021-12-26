
#include "GameModel.h"

GameModel::GameModel(const std::string& path) {

    mesh.loadModelFromFile(path);
    transform = std::make_shared<Transform>();
}

void GameModel::render() {
    mesh.render(transform->getMatrix());
    if(useCollision){
        col->drawDebug();
    }
}

void GameModel::update(SetupWindow &gScene) {
}

void GameModel::onCollision(GameModel *other) {
    //std::cout << "colliding" << std::endl;
}




