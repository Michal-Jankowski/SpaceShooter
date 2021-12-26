//
// Created by aklin on 15.11.2021.
//

#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../GameScene.h"
#include "../elements/Laser.h"

Ship::Ship(const std::string &modelPath, std::shared_ptr<Camera> &cameraRef) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(transform, 2.0f, false);

    this->cameraRef = cameraRef;
}

void Ship::update(SetupWindow* scene) {
    GameModel::update(scene);

    ///ATTACH TO CAM
    transform->setPosition(
            cameraRef->getEye() +
            (distCamOffset * cameraRef->getNormalizedViewVector()) +
            heightCamOffset);
    transform->setLookAt(cameraRef->getNormalizedViewVector());

    ///LASER
    if(scene->mouseButtonPressed(m_shootMouseKeyCode)){
        GameScene* gScene = dynamic_cast<GameScene*>(scene);
        glm::vec3 startPos = transform->getPosition();
        glm::vec3 endPos = startPos +(cameraRef->getNormalizedViewVector() * laserLength);
        gScene->addObject(std::make_unique<Laser>(startPos, endPos, 10.0f));


    }
}
