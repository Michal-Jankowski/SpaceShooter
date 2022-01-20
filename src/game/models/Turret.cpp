

#include "Turret.h"
#include "../GameScene.h"
#include "Planet.h"

void Turret::update(SetupWindow *scene) {
    Enemy::update(scene);
    transform->setScale(glm::vec3(2.0f));

    auto* gScene = dynamic_cast<GameScene*>(scene);

    auto collisionHandler = gScene->getCollisionHandler();
    bool lineOfSight = collisionHandler.inLineOfSight(*this, gScene->getPlayer(), &isSightInterruptor);

    if(lineOfSight){
        shootAttemptTimer += (float)scene->getDeltaTime();
        if(shootAttemptTimer >= shootAttemptInterval){
            shootAttemptTimer = -0.01f;
            tryShoot(gScene);
        }
    }
    else {
        //shootAttemptTimer = 0.0f;
    }
}

void Turret::tryShoot(GameScene *gScene) {
    std::cout << "SHOOTING" << std::endl;
}

void Turret::drawHud(GameHUD *hud) {
    Enemy::drawHud(hud);
    hud->addLines(string_utils::formatString("Shoot timer: {}", shootAttemptTimer), 1);
}

bool Turret::isSightInterruptor(GameObject* go) {
    return dynamic_cast<Planet*>(go) != nullptr;
}