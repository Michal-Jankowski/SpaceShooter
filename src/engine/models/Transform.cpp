#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Transform.h"

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
    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), pos);
    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), angle(rotation), axis(rotation));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 modelMatrix = translationMat * rotationMat * scaleMat;
    return modelMatrix;
}

void Transform::setLookAt(glm::vec3 direction, glm::vec3 up){
    rotation = glm::quatLookAt(glm::normalize(direction), up);
}

void Transform::rotateEuler(float x, float y, float z) {
    glm::mat4 rotationMatrix = glm::eulerAngleXYZ(x,y,z);
    glm::quat rotateQuat = glm::quat_cast(rotationMatrix);
    rotation = rotation * rotateQuat;
}


