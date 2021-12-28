

#include "Planet.h"
#include "../../engine/utils/MathUtils.h"
#include "../GameScene.h"
#include "Enemy.h"
#include "Collectible.h"
#include <random>

Planet::Planet(float size, SetupWindow* scene) : GameModel(MODEL_PATH) {
    auto* gScene = dynamic_cast<GameScene*>(scene);

    for (int i = 0; i < enemies; ++i) {
        float theta = PI *std::rand();
        float phi = TWO_PI * std::rand();
        glm::vec3 pos = MathUtils::sphericalToCartesianRadians(size,phi,theta);

        auto enemy = std::make_unique<Enemy>();
        enemy->transform->setPosition(pos + transform->getPosition());
        gScene->addObject(std::move(enemy));
    }

    for (int i = 0; i < maxCollectibles; ++i) {
        float theta = PI *std::rand();
        float phi = TWO_PI * std::rand();
        glm::vec3 pos = MathUtils::sphericalToCartesianRadians(size,phi,theta);

        auto collectible = std::make_unique<Collectible>();
        collectible->transform->setPosition(pos + transform->getPosition());
        gScene->addObject(std::move(collectible));
    }

    //transform->setScale(glm::vec3(size));
}

void Planet::update(SetupWindow *gScene) {
    GameObject::update(gScene);
}

void Planet::onCollision(GameObject *other) {
    GameObject::onCollision(other);
}

bool Planet::isValidCollisionTarget(GameObject *other) const {
    return false;
}
