

#include "Laser.h"
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

Laser::Laser(glm::vec3 from, glm::vec3 to, float lifetime) : line(from,to) {
    timer = lifetime;
    std::cout << "creating laser from: " << to_string(from) << " to: " << to_string(to) << std::endl;
}

void Laser::update(SetupWindow *gScene) {
    GameObject::update(gScene);
    //std::cout << "updating laser"  << std::endl;
    auto deltaTime = (float)gScene->getDeltaTime();
    glm::vec3 dir = line.getEndPosition() - line.getStartPosition();
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


