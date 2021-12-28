

#include <iostream>
#include "MathUtils.h"

glm::vec3 MathUtils::sphericalToCartesianRadians(float radius, float phi, float theta) {
    return glm::vec3(
         cos(phi) * sin(theta) ,
         sin(phi) * sin(theta) ,
         cos(theta)
    ) * radius;
}

glm::vec3 MathUtils::sphericalToCartesianAngles(float radius, float phi, float theta) {
    return glm::vec3(
         radius * cos(phi * PI / 180.0) * sin(theta * PI / 180.0) ,
         radius * sin(phi * PI / 180.0) * sin(theta * PI / 180.0) ,
         radius * cos(theta * PI / 180.0)
    );
}
