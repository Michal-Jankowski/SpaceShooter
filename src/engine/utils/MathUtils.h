

#ifndef SPACESHOOTER_MATHUTILS_H
#define SPACESHOOTER_MATHUTILS_H


#include <glm/vec3.hpp>

#define PI 3.14159265
#define TWO_PI 2 * 3.14159265

class MathUtils {
public:
    static glm::vec3 sphericalToCartesianAngles(float radius, float phi, float theta);
    static glm::vec3 sphericalToCartesianRadians(float radius, float phi, float theta);
};


#endif //SPACESHOOTER_MATHUTILS_H
