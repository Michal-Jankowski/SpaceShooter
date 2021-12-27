
#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform() {
    pos = glm::vec3(0.0f,0.0f,0.0f);
    rotation = glm::quat(0.0f,0.0f,0.0f, 1.0f);
    scale =  glm::vec3(1.0f,1.0f,1.0f);
}

glm::vec3 Transform::getPosition() {
    return pos;
}

void Transform::setPosition(glm::vec3 newPos) {
    pos = newPos;
}

void Transform::setPosition(float x , float y, float z) {
    setPosition(glm::vec3(x,y,z));
}


void Transform::moveBy(glm::vec3 distance) {
    pos += distance;
}

void Transform::setScale(glm::vec3 newScale) {
    scale = newScale;
}

glm::vec3 Transform::getScale() {
    return scale;
}

void Transform::scaleTimes(glm::vec3 diff) {
    scale *= diff;
}

glm::mat4 Transform::getMatrix() {
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), pos);
    modelMatrix = glm::rotate(modelMatrix, angle(rotation), axis(rotation));
    modelMatrix = glm::scale(modelMatrix, scale);
    return modelMatrix;
}

void Transform::setLookAt(glm::vec3 direction, glm::vec3 up){
    rotation = glm::quatLookAt(direction, up);
}


