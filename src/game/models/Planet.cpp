

#include "Planet.h"
#include "../../engine/utils/MathUtils.h"
#include "../GameScene.h"
#include "Enemy.h"
#include "Collectible.h"
#include <random>

Planet::Planet(float size, SetupWindow* scene) : GameModel(MODEL_PATH) {
    auto* gScene = dynamic_cast<GameScene*>(scene);

    for (int i = 0; i < maxEnemies; ++i) {
        float theta = TWO_PI *std::rand();
        float phi = acos(2.0f * std::rand() - 1.0f);
        float rho = size;
        glm::vec3 pos = MathUtils::sphericalToCartesian(rho,phi,theta);

        auto enemy = std::make_unique<Enemy>();
        enemy->transform->setPosition(pos);
        gScene->addObject(std::move(enemy));
    }

    for (int i = 0; i < maxCollectibles; ++i) {
        float theta = TWO_PI * std::rand();
        float phi = acos(2.0f * std::rand() - 1.0f);
        float rho = size;
        glm::vec3 pos = MathUtils::sphericalToCartesian(rho,phi,theta);

        auto collectible = std::make_unique<Collectible>();
        collectible->transform->setPosition(pos);
        gScene->addObject(std::move(collectible));
    }

    transform->setScale(glm::vec3(size));
}

void Planet::update(SetupWindow *gScene) {
    GameObject::update(gScene);
}

void Planet::onCollision(GameObject *other) {
    GameObject::onCollision(other);
}
