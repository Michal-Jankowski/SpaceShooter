#include "Collectible.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"

Collectible::Collectible(SetupWindow* scene)
    : GameModel(scene, MODEL_PATH)
    , m_outline(scene, this, this, glm::mat4(1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f)) {
    col = std::make_unique<SphereCollider>(transform.get(),2.0f, true);
}

void Collectible::update() {
    GameModel::update();
    m_outline.render();
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
    //hud->addLines(string_utils::formatString("Collectible spawned at: ({}; {}; {})", pos.x, pos.y, pos.z), 1);
}

bool Collectible::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Ship*>(other) != nullptr;
}
