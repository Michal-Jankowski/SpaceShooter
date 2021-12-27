//
// Created by aklin on 15.11.2021.
//

#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../GameScene.h"
#include "../elements/Laser.h"

Ship::Ship(std::shared_ptr<Camera> cameraRef) : GameModel(MODEL_PATH), m_camera(std::move(cameraRef)) {
    col = std::make_unique<SphereCollider>(transform, 2.0f, true);
}

void Ship::update(SetupWindow* scene) {
    GameModel::update(scene);

    ///ATTACH TO CAM
    transform->setPosition(
        m_camera->getEye() +
            (distCamOffset * m_camera->getNormalizedViewVector()) +
            heightCamOffset);
    transform->setLookAt(m_camera->getNormalizedViewVector());

    shootCheck(scene);
}

void Ship::shootCheck(SetupWindow* scene) {

    if(shootTimer > 0.0f){
        shootTimer -= (float)scene->getDeltaTime();
        return;
    }

    if(scene->mouseButtonPressed(m_shootMouseKeyCode)){
        auto* gScene = dynamic_cast<GameScene*>(scene);
        glm::vec3 startPos = transform->getPosition() - (m_camera->getNormalizedViewVector() * laserSpeedStartCompensation);
        glm::vec3 endPos = startPos +(m_camera->getNormalizedViewVector() * laserLength);
        gScene->addObject(std::make_unique<Laser>(startPos, endPos, laserLifetime));
        shootTimer = shootTimeout;
    }
}

void Ship::drawHud(GameHUD *hud) {
    hud->addLines("aaaaaaa from Ship", 1);
}
