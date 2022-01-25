#include <string>
#include "Ship.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../GameScene.h"
#include "../elements/Laser.h"
#include "../../engine/utils/RandomGenerator.h"

Ship::Ship(SetupWindow* scene, std::shared_ptr<Camera> cameraRef) : GameModel(scene, MODEL_PATH), m_camera(std::move(cameraRef)) {
    col = std::make_unique<SphereCollider>(transform.get(), 1.5f);
    enemiesShot = 0;
    collectiblesFound = 0;
    init();
}

void Ship::init() {
    m_camera->returnToInitPosition();
    lives = initLives;
}

void Ship::update() {
    GameModel::update();

    ///ATTACH TO CAM
    transform->setPosition(
        m_camera->getEye() +
            (distCamOffset * m_camera->getNormalizedViewVector()) +
            heightCamOffset);
    transform->setLookAt(m_camera->getNormalizedViewVector());

    shootCheck();
}

void Ship::shootCheck() {

    if(shootTimer > 0.0f){
        shootTimer -= (float)scene->getDeltaTime();
        return;
    }

    if(scene->mouseButtonPressed(m_shootMouseKeyCode)){
        auto* gScene = dynamic_cast<GameScene*>(scene);
        glm::vec3 startPos = transform->getPosition() - (m_camera->getNormalizedViewVector() * Laser::laserSpeedStartCompensation);
        glm::vec3 endPos = startPos +(m_camera->getNormalizedViewVector() * Laser::laserLength);
        gScene->addObject(std::make_unique<Laser>(scene, startPos, endPos, Laser::laserLifetime, this));
        shootTimer = shootTimeout;
    }
}

void Ship::drawHud(GameHUD *hud) {
    hud->addLines(string_utils::formatString("Lives: {}", lives), 1);
    hud->addLines(string_utils::formatString("Enemies shot: {}/{}", enemiesShot, totalEnemies), 1);
    hud->addLines(string_utils::formatString("Collectibles found: {}/{}", collectiblesFound, totalCollectibles), 1);
}

void Ship::addPoint(Ship::PointType type) {
    switch(type){
        case enemyPoint:
            enemiesShot++;
            break;
        case collectiblePoint:
            collectiblesFound++;
            break;
    }
}

bool Ship::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Laser*>(other) != nullptr;
}

void Ship::damage(bool autoKill) {
    lives -= 1;
    if(autoKill || lives <= 0){
        auto gScene = dynamic_cast<GameScene*>(scene);
        gScene->reinitObjects();
    }
}

void Ship::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    if(auto laser = dynamic_cast<Laser*>(other)){
        if(dynamic_cast<Ship*>(laser->getShooter()) == nullptr){
            if(RandomGenerator::getInstance().fromZeroToOne() < laserDmgChance) {
                damage();
            }
        }
    }
}

void Ship::reinit() {
    GameModel::reinit();
    init();
}

void Ship::addTotalTarget(int enemies, int collectibles) {
    totalEnemies += enemies;
    totalCollectibles += collectibles;
}


