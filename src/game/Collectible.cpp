//
// Created by aklin on 15.11.2021.
//

#include "Collectible.h"
#include "../GameScene.h"
#include "../SphereCollider.h"

Collectible::Collectible(const std::string &modelPath, glm::vec3 pos) : GameModel(modelPath, pos) {
    col = std::make_unique<SphereCollider>(2.0f, true);
    useCollision = true;
}

void Collectible::update(SetupWindow &gScene) {
    GameModel::update(gScene);
}

void Collectible::onCollision(GameModel *other) {
    GameModel::onCollision(other);
    awaitingDestroy = true;
}
