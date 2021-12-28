

#include <iostream>
#include "MathUtils.h"

glm::vec3 MathUtils::sphericalToCartesianRadians(float radius, float phi, float theta) {
    return glm::vec3(
            cos(theta) * cos(phi),
            cos(theta) * sin(phi),
            sin(theta)
    ) * radius;
}

glm::vec3 MathUtils::sphericalToCartesianAngles(float radius, float phi, float theta) {
    return glm::vec3(
            cos(theta * PI / 180.0) * cos(phi * PI / 180.0),
            cos(theta * PI / 180.0) * sin(phi * PI / 180.0),
            sin(theta * PI / 180.0)
    ) * radius;
}
