#include "Collectible.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"

Collectible::Collectible() : GameModel(MODEL_PATH) {
    col = std::make_unique<SphereCollider>(transform,2.0f, true);

}

void Collectible::update(SetupWindow* gScene) {
    GameModel::update(gScene);
}

void Collectible::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    //std::cout << "colliding" << std::endl;
    //std::cout << col->debugEnable << std::endl;
    if(auto* ship = dynamic_cast<Ship*>(other)) {
        ship->addPoint(Ship::collectiblePoint);
        awaitingDestroy = true;
    }
}

void Collectible::drawHud(GameHUD *hud) {
    GameModel::drawHud(hud);
    glm::vec3 pos = transform->getPosition();
    hud->addLines(string_utils::formatString("collectiblePoint at: {} {} {}", pos.x, pos.y, pos.z), 1);
}
