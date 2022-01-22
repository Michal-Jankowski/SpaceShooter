

#include "Turret.h"
#include "../GameScene.h"
#include "Planet.h"
#include "../../engine/utils/RandomGenerator.h"

void Turret::update(SetupWindow *scene) {
    Enemy::update(scene);
    transform->setScale(glm::vec3(2.0f));

    auto* gScene = dynamic_cast<GameScene*>(scene);

    auto collisionHandler = gScene->getCollisionHandler();
    bool lineOfSight = collisionHandler.inLineOfSight(*this, gScene->getPlayer(), &isSightInterruptor);

    if(lineOfSight){
        shootAttemptTimer += (float)scene->getDeltaTime();
        if(shootAttemptTimer >= shootAttemptInterval){
            shootAttemptTimer = 0.0f;
            tryShoot(gScene);
        }
    }
    else {
        shootAttemptTimer = 0.0f;
    }
}

void Turret::tryShoot(GameScene *gScene) {
    //std::cout << "SHOOTING" << std::endl;
    auto shipPos = gScene->getPlayer().transform->getPosition();
    glm::vec3 pos = RandomGenerator::getInstance().onSurfaceOfUnitSphere();
    pos *= shootRandomSize;
    pos += shipPos;

    glm::vec3 dir = glm::normalize(shipPos - transform->getPosition());

    glm::vec3 startPos = transform->getPosition() - (dir * Laser::laserSpeedStartCompensation);
    glm::vec3 endPos = startPos +(dir * Laser::laserLength);
    gScene->addObject(std::make_unique<Laser>(startPos, endPos, Laser::laserLifetime, this));
}

void Turret::drawHud(GameHUD *hud) {
    Enemy::drawHud(hud);
    hud->addLines(string_utils::formatString("Shoot timer: {}", shootAttemptTimer), 1);
}

bool Turret::isSightInterruptor(GameObject* go) {
    return dynamic_cast<Planet*>(go) != nullptr;
}