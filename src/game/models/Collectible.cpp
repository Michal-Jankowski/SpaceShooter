#include "Collectible.h"
#include "../../engine/collisions/SphereCollider.h"
#include "Ship.h"

Collectible::Collectible(SetupWindow* scene)
    : GameModel(scene, MODEL_PATH)
    , m_outline(scene,
                this, this,
                glm::mat4(1.0f),
                glm::vec4(1.0f, 0.0f, 1.0f, 0.0f),
                glm::vec3(9.0f, 9.0f, 9.0f)) {
    col = std::make_unique<SphereCollider>(transform.get(), 2.0f);
}

void Collectible::update() {
    GameModel::update();
}

void Collectible::render() {
    GameModel::render();
    m_outline.render();
}

void Collectible::onCollision(GameObject *other) {
    GameModel::onCollision(other);
    if(auto* ship = dynamic_cast<Ship*>(other)) {
        ship->addPoint(Ship::collectiblePoint);
        awaitingDestroy = true;
    }
}


bool Collectible::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Ship*>(other) != nullptr;
}


