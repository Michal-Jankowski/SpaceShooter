

#ifndef SPACESHOOTER_COLLISIONMATH_H
#define SPACESHOOTER_COLLISIONMATH_H


#include <glm/vec3.hpp>

class CollisionMath {
public:
    static bool LineSphereCollision(glm::vec3 lineStart, glm::vec3 lineEnd, glm::vec3 spherePos, float sphereRadius);
};


#endif //SPACESHOOTER_COLLISIONMATH_H
