#include <array>
#include <glm/geometric.hpp>
#include "CollisionMath.h"


bool CollisionMath::lineSphereCollision(glm::vec3 lineStart, glm::vec3 lineEnd, glm::vec3 spherePos, float sphereRadius) {

    glm::vec3 dist = lineEnd - lineStart;
    float t = glm::length(dist);
    glm::vec3 rayDir = dist / t;

    glm::vec3 posDiff = lineStart - spherePos;

    float a = glm::dot(rayDir, rayDir);
    float b = 2.0f * dot(posDiff, rayDir);
    float c = dot(posDiff, posDiff) - sphereRadius * sphereRadius;

    auto delta = (b * b) - (4.0f * a * c);

    if (delta < 0) {
        return false;
    }
    else {
        float squared = sqrt(delta);
        float t0 = (-b - squared) / (2.0f * a);
        float t1 = (-b + squared) / (2.0f * a);

        if((t0 > 0.0f && t0 < t) || (t1 > 0.0f && t1 < t)){
            return true;
        }
        //intersection before start point or after end point
        else{
            return false;
        }
    }
}
