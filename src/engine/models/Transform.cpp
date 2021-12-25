
#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform() {
    pos = glm::vec3(0.0f,0.0f,0.0f);
    rotAxis = glm::vec3(1.0f,0.0f,0.0f);
    rotAngle = 0;
    scale =  glm::vec3(1.0f,1.0f,1.0f);
}

glm::vec3 Transform::getPosition() {
    return pos;
}

void Transform::setPosition(glm::vec3 newPos) {
    pos = newPos;
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
    modelMatrix = glm::rotate(modelMatrix, rotAngle, rotAxis);
    modelMatrix = glm::scale(modelMatrix, scale);
    return modelMatrix;
}

