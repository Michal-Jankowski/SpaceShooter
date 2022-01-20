

#include "Planet.h"
#include "../GameScene.h"
#include "Collectible.h"
#include "Turret.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../../engine/utils/RandomGenerator.h"

Planet::Planet(float size, SetupWindow* scene, const glm::vec3 &position) : GameModel(MODEL_PATH, position) {

    col = std::make_unique<SphereCollider>(transform.get(),size, true);

    auto* gScene = dynamic_cast<GameScene*>(scene);

    auto r = RandomGenerator::getInstance();

    for (int i = 0; i < enemies; ++i) {
        glm::vec3 pos = r.onSurfaceOfUnitSphere() * size * collectiblesOffset;

        auto enemy = std::make_unique<Turret>();
        enemy->transform->setPosition(pos + transform->getPosition());
        enemy->transform->setLookAt(pos);
        gScene->addObject(std::move(enemy));
    }

    for (int i = 0; i < collectibles; ++i) {
        glm::vec3 pos = r.onSurfaceOfUnitSphere() * size * collectiblesOffset;

        auto collectible = std::make_unique<Collectible>();
        collectible->transform->setPosition(pos + transform->getPosition());
        gScene->addObject(std::move(collectible));
    }

    transform->setScale(glm::vec3(size));
}

void Planet::update(SetupWindow *gScene) {
    GameObject::update(gScene);
}

void Planet::onCollision(GameObject *other) {
    GameObject::onCollision(other);
    auto ship = dynamic_cast<Ship*>(other);
    if(ship != nullptr){
        //ship->damage(true);
    }
}

bool Planet::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Ship*>(other) != nullptr;
}


