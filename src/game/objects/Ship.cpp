//
// Created by aklin on 15.11.2021.
//

#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"

Ship::Ship(const std::string &modelPath) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(2.0f, true);
    useCollision = true;
}

void Ship::update(SetupWindow &scene) {
    GameModel::update(scene);
    transform.moveBy(glm::vec3(0.0f, 0.0f, -scene.getDeltaTime()));
    //scene.keyPressed()

}
