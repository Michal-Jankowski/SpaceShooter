

#include "Turret.h"
#include "../GameScene.h"

void Turret::update(SetupWindow *scene) {
    Enemy::update(scene);
    transform->setScale(glm::vec3(2.0f));

    auto* gScene = dynamic_cast<GameScene*>(scene);

    auto collisionHandler = gScene->getCollisionHandler();
    bool lineOfSight = collisionHandler.inLineOfSight(*this, gScene->getPlayer());

    if(lineOfSight){
        std::cout << "I SEEEE YOUUUUUUU" << std::endl;
    }
}
