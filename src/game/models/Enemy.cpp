#include "Enemy.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"
#include "../elements/Laser.h"


Enemy::Enemy(const std::string &modelPath) : GameModel(modelPath) {
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
    else if(dynamic_cast<Laser*>(other) != nullptr){
        awaitingDestroy = true;
    }
}