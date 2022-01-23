

#include "Laser.h"
#include "../../engine/collisions/LineCollider.h"
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

Laser::Laser(SetupWindow *scene, glm::vec3 from, glm::vec3 to, float lifetime,GameObject* shotFrom) : GameObject(scene), line(from,to) {
    timer = lifetime;
    this->shotFrom = shotFrom;
    glm::vec3 dir = line.getNormalisedDir();
    col = std::make_unique<LineCollider>(nullptr, line.getStartPosition(), line.getStartPosition() + (dir * lineCollisionCheckLength));
}

void Laser::update() {
    GameObject::update();
    //std::cout << "updating laser"  << std::endl;
    auto deltaTime = (float)scene->getDeltaTime();
    glm::vec3 dir = line.getNormalisedDir();
    glm::vec3 offset = dir * speed * deltaTime;
    std::vector<glm::vec3> linePoints{ line.getStartPosition() + offset, line.getEndPosition() + offset };
    line.setPosition(linePoints);
    timer -= deltaTime;
    if(timer < 0){
        awaitingDestroy = true;
        line.~Line();
        shotFrom = nullptr;
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


