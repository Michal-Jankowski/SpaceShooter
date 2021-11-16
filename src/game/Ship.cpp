//
// Created by aklin on 15.11.2021.
//

#include "Ship.h"
#include "../SetupWindow.h"
#include "../GameScene.h"
#include "../SphereCollider.h"

Ship::Ship(const std::string &modelPath) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(glm::vec3(0.0f), 1.0f);
    useCollision = true;
}

void Ship::update(SetupWindow &scene) {
    GameModel::update(scene);
    moveBy(glm::vec3(0.0f, 0.0f, -scene.getDeltaTime()));
    col->pos = getPosition();
}
