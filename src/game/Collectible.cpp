//
// Created by aklin on 15.11.2021.
//

#include "Collectible.h"
#include "../GameScene.h"
#include "../SphereCollider.h"

Collectible::Collectible(const std::string &modelPath) : GameModel(modelPath) {
    col = std::make_unique<SphereCollider>(glm::vec3(0.0f), 1.0f, true);
    useCollision = true;
}

void Collectible::update(SetupWindow &gScene) {
    GameModel::update(gScene);
    col->pos = getPosition();
}

void Collectible::onCollision(GameModel *other) {
    GameModel::onCollision(other);
    awaitingDestroy = true;
    std::cout << "COLLLISION" << std::endl;
}
