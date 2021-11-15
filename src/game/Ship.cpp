//
// Created by aklin on 15.11.2021.
//

#include "Ship.h"
#include "../SetupWindow.h"
#include "../GameScene.h"

Ship::Ship(const std::string &modelPath) : GameModel(modelPath) {

}

void Ship::update(SetupWindow &scene) {
    GameModel::update(scene);
    moveBy(glm::vec3(0.0f, 0.0f, -scene.getDeltaTime()));
}
