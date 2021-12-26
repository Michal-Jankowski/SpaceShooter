

#include "Laser.h"

Laser::Laser(glm::vec3 from, glm::vec3 to, float lifetime, std::shared_ptr<Camera> camera) : line(from,to, camera) {
    timer = lifetime;
    std::cout << "creating laser"  << std::endl;
}

void Laser::update(SetupWindow *gScene) {
    GameObject::update(gScene);
    std::cout << "updating laser"  << std::endl;
}

void Laser::render() {
    GameObject::render();
    line.draw();
}


