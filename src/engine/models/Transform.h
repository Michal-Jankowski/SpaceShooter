

#ifndef SPACESHOOTER_TRANSFORM_H
#define SPACESHOOTER_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
    Transform();

    void setPosition(glm::vec3 newPos);
    void setPosition(float x , float y, float z);
    [[nodiscard]] glm::vec3 getPosition();
    void moveBy(glm::vec3 distance);

    void setLookAt(glm::vec3 direction, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    void rotateEuler(float x, float y, float z);

    void setScale(glm::vec3 newScale);
    [[nodiscard]]  glm::vec3 getScale();
    void scaleTimes(glm::vec3 diff);

    [[nodiscard]] glm::mat4 getMatrix();

private:
    glm::vec3 pos;
    glm::quat rotation;
    glm::vec3 scale;
};


#endif //SPACESHOOTER_TRANSFORM_H
