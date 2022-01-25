#include "Enemy.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"


Enemy::Enemy(SetupWindow *scene, const std::string &model_path) : GameModel(scene, model_path) {
    col = std::make_unique<SphereCollider>(transform.get(),1.8f);
}

Enemy::Enemy(SetupWindow* scene) : Enemy(scene, MODEL_PATH) {

}

void Enemy::update() {
    GameModel::update();
}

void Enemy::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    if(awaitingDestroy){
        return;
    }
    if(auto ship = dynamic_cast<Ship*>(other)){
        ship->damage(true);
    }
    else if(auto laser = dynamic_cast<Laser*>(other)){
        if(auto pShip = dynamic_cast<Ship*>(laser->getShooter())){
            pShip->addPoint(Ship::enemyPoint);
            awaitingDestroy = true;
        }
    }
}


bool Enemy::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Ship*>(other) != nullptr
        || dynamic_cast<Laser*>(other) != nullptr;
}

