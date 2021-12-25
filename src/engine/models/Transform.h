

#ifndef SPACESHOOTER_TRANSFORM_H
#define SPACESHOOTER_TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
public:
    Transform();

    void setPosition(glm::vec3 newPos);
    [[nodiscard]] glm::vec3 getPosition();
    void moveBy(glm::vec3 distance);

//    void setRotation(glm::vec3 axis, float angle);
//    [[nodiscard]] glm::vec3 getRotationAxis();
//    [[nodiscard]] float getRotationAngle();
//    void rotateBy(glm::vec3 axis, float angle);

    void setScale(glm::vec3 newScale);
    [[nodiscard]]  glm::vec3 getScale();
    void scaleTimes(glm::vec3 diff);

    [[nodiscard]] glm::mat4 getMatrix();

private:
    glm::vec3 pos;
    glm::vec3 rotAxis;
    float rotAngle;
    glm::vec3 scale;
};


#endif //SPACESHOOTER_TRANSFORM_H
