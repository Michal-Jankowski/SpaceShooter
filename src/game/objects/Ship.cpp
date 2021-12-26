//
// Created by aklin on 15.11.2021.
//

#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"

Ship::Ship(const std::string &modelPath, std::shared_ptr<Camera> &cameraRef) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(transform, 2.0f, false);
    useCollision = true;

    this->cameraRef = cameraRef;
}

void Ship::update(SetupWindow &scene) {
    GameModel::update(scene);
    transform->setPosition(
            cameraRef->getEye() +
            (distCamOffset * cameraRef->getNormalizedViewVector()) +
            heightCamOffset);
    transform->setLookAt(cameraRef->getNormalizedViewVector());
}
