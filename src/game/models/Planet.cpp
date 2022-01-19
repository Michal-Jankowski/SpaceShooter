

#include "Planet.h"
#include "../../engine/utils/MathUtils.h"
#include "../GameScene.h"
#include "Collectible.h"
#include "Turret.h"
#include "../../engine/collisions/SphereCollider.h"
#include <random>

Planet::Planet(float size, SetupWindow* scene, const glm::vec3 &position) : GameModel(MODEL_PATH, position) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,100);
    col = std::make_unique<SphereCollider>(transform.get(),size, true);

    auto* gScene = dynamic_cast<GameScene*>(scene);

    for (int i = 0; i < enemies; ++i) {
        float theta = PI * (float)dist(rng)/100.0f;
        float phi = TWO_PI * (float)dist(rng)/100.0f;
        glm::vec3 pos = MathUtils::sphericalToCartesianRadians(size * collectiblesOffset,phi,theta);

        auto enemy = std::make_unique<Turret>();
        enemy->transform->setPosition(pos + transform->getPosition());
        enemy->transform->setLookAt(pos);
        gScene->addObject(std::move(enemy));
    }

    for (int i = 0; i < collectibles; ++i) {
        float theta = PI * (float)dist(rng)/100.0f;
        float phi = TWO_PI * (float)dist(rng)/100.0f;
        glm::vec3 pos = MathUtils::sphericalToCartesianRadians(size * collectiblesOffset,phi,theta);

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
        ship->damage(true);
    }
}

bool Planet::isValidCollisionTarget(GameObject *other) const {
    return dynamic_cast<Ship*>(other) != nullptr;
}
