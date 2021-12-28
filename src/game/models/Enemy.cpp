#include "Enemy.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"
#include "../elements/Laser.h"


Enemy::Enemy() : GameModel(MODEL_PATH) {
    col = std::make_unique<SphereCollider>(transform,2.0f, true);
}

void Enemy::update(SetupWindow* gScene) {
    GameModel::update(gScene);
}

void Enemy::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    if(dynamic_cast<Ship*>(other) != nullptr){
        other->awaitingDestroy = true;
    }
    else if(auto* laser = dynamic_cast<Laser*>(other)){
        if(auto* ship = dynamic_cast<Ship*>(laser->getShooter())){
            ship->addPoint(Ship::enemyPoint);
        }
        awaitingDestroy = true;
    }
}

void Enemy::drawHud(GameHUD *hud) {
    glm::vec3 pos = transform->getPosition();
    hud->addLines(string_utils::formatString("enemyPoint at: {} {} {}", pos.x, pos.y, pos.z), 1);
}
