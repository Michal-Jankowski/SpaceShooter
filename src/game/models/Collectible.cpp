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
    //std::cout << col->debugEnable << std::endl;
    awaitingDestroy = true;
}
