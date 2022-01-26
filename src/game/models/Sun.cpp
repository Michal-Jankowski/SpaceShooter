

#include "Sun.h"

Sun::Sun(SetupWindow *scene, float size, const glm::vec3 &position, PointLight* pointLightRef, float orbit, float orbitSpeed)
         : Planet(scene, size, false, MODEL_PATH, position),
         orbit(orbit), orbitSpeed(orbitSpeed){
    this->pointLightRef = pointLightRef;
    this->size = size;
    initPos = position;
}

void Sun::update() {
    Planet::update();

    auto counter = scene->getTimeElapsed() * orbitSpeed;
    glm::vec3 circle = glm::vec3(orbit * cos(counter), 0.0f, orbit * sin(counter));
    transform->setPosition(circle + initPos);
    pointLightRef->setPosition(circle + initPos);
}
