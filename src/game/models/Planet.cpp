

#include "Planet.h"
#include "../GameScene.h"
#include "Collectible.h"
#include "Turret.h"
#include "../../engine/collisions/SphereCollider.h"
#include "../../engine/utils/RandomGenerator.h"

Planet::Planet(SetupWindow *scene, float size, bool generateSurroundings, const std::string &modelPath,
               const glm::vec3 &position) : GameModel(scene, modelPath, position)  {

    col = std::make_unique<SphereCollider>(transform.get(),size * 0.9f, true);

    if(generateSurroundings) {
        auto gScene = dynamic_cast<GameScene *>(scene);
        //Ship player = gScene->getPlayer();

        auto r = RandomGenerator::getInstance();

        for (int i = 0; i < enemies; ++i) {
            glm::vec3 pos = r.onSurfaceOfUnitSphere() * size * collectiblesOffset;

            auto enemy = std::make_unique<Turret>(scene);
            enemy->transform->setPosition(pos + transform->getPosition());
            enemy->transform->setLookAt(pos);
            gScene->addObject(std::move(enemy));
        }

        for (int i = 0; i < collectibles; ++i) {
            glm::vec3 pos = r.onSurfaceOfUnitSphere() * size * collectiblesOffset;

            auto collectible = std::make_unique<Collectible>(scene);
            collectible->transform->setPosition(pos + transform->getPosition());
            gScene->addObject(std::move(collectible));
        }
    }

    transform->setScale(glm::vec3(size));
}

Planet::Planet(SetupWindow* scene, float size, bool generateSurroundings, const glm::vec3 &position)
 : Planet(scene, size, generateSurroundings, MODEL_PATH, position) {}

void Planet::update() {
    GameObject::update();
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





