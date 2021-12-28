

#include <iostream>
#include "MathUtils.h"

glm::vec3 MathUtils::sphericalToCartesianRadians(float radius, float phi, float theta) {
    return glm::vec3(
            radius * cos(theta) * cos(phi),
            radius * cos(theta) * sin(phi),
            radius * sin(theta)
    ) * radius;
}

glm::vec3 MathUtils::sphericalToCartesianAngles(float radius, float phi, float theta) {
    return glm::vec3(
         radius * cos(theta * PI / 180.0) * cos(phi * PI / 180.0),
         radius * cos(theta * PI / 180.0) * sin(phi * PI / 180.0),
         radius * sin(theta * PI / 180.0)
    );
}
