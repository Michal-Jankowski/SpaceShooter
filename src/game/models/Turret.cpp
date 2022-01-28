

#include "Turret.h"
#include "../GameScene.h"
#include "Planet.h"
#include "../../engine/utils/RandomGenerator.h"

void Turret::update() {
    Enemy::update();
    transform->setScale(glm::vec3(2.0f));

    auto* gScene = dynamic_cast<GameScene*>(scene);

    auto collisionHandler = gScene->getCollisionHandler();
    bool lineOfSight = collisionHandler.inLineOfSight(*this, *gScene->getPlayer(), &isSightInterruptor);

    if(lineOfSight){
        shootAttemptTimer += (float)scene->getDeltaTime();
        if(shootAttemptTimer >= randomShootInterval){
            shootAttemptTimer = 0.0f;
            randomShootInterval = 2.0f * RandomGenerator::getInstance().fromZeroToOne() * shootAttemptInterval;
            tryShoot(gScene);
        }
    }
    else {
        shootAttemptTimer = 0.0f;
    }
}

void Turret::tryShoot(GameScene *gScene) {
    auto shipPos = gScene->getPlayer()->transform->getPosition();
    glm::vec3 pos = RandomGenerator::getInstance().onSurfaceOfUnitSphere();
    pos = pos * shootRandomSize;
    pos += shipPos;

    glm::vec3 dir = glm::normalize(pos - transform->getPosition());

    glm::vec3 startPos = transform->getPosition() - (dir * Laser::laserSpeedStartCompensation);
    glm::vec3 endPos = startPos +(dir * Laser::laserLength);
    gScene->addObject(std::make_unique<Laser>(scene, startPos, endPos, Laser::laserLifetime, this));
}

bool Turret::isSightInterruptor(GameObject* go) {
    return dynamic_cast<Planet*>(go) != nullptr;
}

Turret::Turret(SetupWindow *scene) : Enemy(scene, MODEL_PATH) {
    randomShootInterval = shootAttemptInterval;
}

void Turret::renderDebug() {
    GameObject::renderDebug();
    auto* gScene = dynamic_cast<GameScene*>(scene);
    auto collisionHandler = gScene->getCollisionHandler();
    bool lineOfSight = collisionHandler.inLineOfSight(*this, *gScene->getPlayer(), &isSightInterruptor);

    Line l = Line(transform->getPosition(), gScene->getPlayer()->transform->getPosition());
    l.setColor(lineOfSight ? greenColor : redColor);
    l.draw();
}
