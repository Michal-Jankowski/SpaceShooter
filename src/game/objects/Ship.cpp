//
// Created by aklin on 15.11.2021.
//

#include "Ship.h"

Ship::Ship(const std::string &modelPath, glm::vec3 pos) : GameModel(modelPath, pos) {
    col = std::make_unique<SphereCollider>(2.0f, true);
    useCollision = true;
}

void Ship::update(SetupWindow &scene) {
    GameModel::update(scene);
    moveBy(glm::vec3(0.0f, 0.0f, -scene.getDeltaTime()));

}
