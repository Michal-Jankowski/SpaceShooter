//
// Created by aklin on 15.11.2021.
//

#include "Collectible.h"
#include "../../engine/collisions/SphereCollider.h"

Collectible::Collectible(const std::string &modelPath) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(transform,2.0f, true);

}

void Collectible::update(SetupWindow* gScene) {
    GameModel::update(gScene);
}

void Collectible::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    //std::cout << "colliding" << std::endl;
    awaitingDestroy = true;
}
