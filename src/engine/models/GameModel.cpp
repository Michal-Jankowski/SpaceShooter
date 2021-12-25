
#include "GameModel.h"

GameModel::GameModel(const std::string& path) {

    mesh.loadModelFromFile(path);
}

void GameModel::render() {
    mesh.render(transform.getMatrix());
    if(useCollision){
        col->drawDebug();
    }
}

void GameModel::update(SetupWindow &gScene) {
    if (col) {
        col->pos = transform.getPosition();
    }
}

void GameModel::onCollision(GameModel *other) {
    //std::cout << "colliding" << std::endl;
}




