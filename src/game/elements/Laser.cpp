

#include "Laser.h"
#include "../../engine/collisions/LineCollider.h"
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

Laser::Laser(glm::vec3 from, glm::vec3 to, float lifetime,GameObject* shotFrom) : line(from,to) {
    timer = lifetime;
    this->shotFrom = shotFrom;
    glm::vec3 dir = line.getNormalisedDir();
    col = std::make_unique<LineCollider>(nullptr,
                                         line.getStartPosition(),
                                         line.getStartPosition() + (dir * lineCollisionCheckLength));
}

void Laser::update(SetupWindow *gScene) {
    GameObject::update(gScene);
    //std::cout << "updating laser"  << std::endl;
    auto deltaTime = (float)gScene->getDeltaTime();
    glm::vec3 dir = line.getNormalisedDir();
    glm::vec3 offset = dir * speed * deltaTime;
    line.setPosition(line.getStartPosition() + offset,
                     line.getEndPosition() + offset);
    timer -= deltaTime;
    if(timer < 0){
        awaitingDestroy = true;
    }
}

void Laser::render() {
    GameObject::render();
    line.draw();
}

GameObject *Laser::getShooter() {
    return shotFrom;
}

bool Laser::isValidCollisionTarget(GameObject *other) const {
    return false;
}


