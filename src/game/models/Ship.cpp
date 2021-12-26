//
// Created by aklin on 15.11.2021.
//

#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../GameScene.h"
#include "../elements/Laser.h"

Ship::Ship(const std::string& modelPath,  std::shared_ptr<Camera> cameraRef) : GameModel(modelPath), m_camera(std::move(cameraRef)) {
    col = std::make_unique<SphereCollider>(transform, 2.0f, false);
}

void Ship::update(SetupWindow* scene) {
    GameModel::update(scene);

    ///ATTACH TO CAM
    transform->setPosition(
        m_camera->getEye() +
            (distCamOffset * m_camera->getNormalizedViewVector()) +
            heightCamOffset);
    transform->setLookAt(m_camera->getNormalizedViewVector());

    ///LASER
    if(scene->mouseButtonPressed(m_shootMouseKeyCode)){
        GameScene* gScene = dynamic_cast<GameScene*>(scene);
        glm::vec3 startPos = transform->getPosition();
        glm::vec3 endPos = startPos +(m_camera->getNormalizedViewVector() * laserLength);
        gScene->addObject(std::make_unique<Laser>(startPos, endPos, 10.0f));


    }
}
