#include <array>
#include "CollisionMath.h"


bool CollisionMath::lineSphereCollision(glm::vec3 lineStart, glm::vec3 lineEnd, glm::vec3 spherePos, float sphereRadius) {
    std::array<glm::vec3, 2> linePoints{lineStart, lineEnd};

    // solving quadratic equation of the form: au^2 + bu + c = 0
    glm::vec3 diffValues = glm::vec3(linePoints[1].x - linePoints[0].x, linePoints[1].y - linePoints[0].y, linePoints[1].z - linePoints[0].z);

    auto a = diffValues.x * diffValues.x + diffValues.y * diffValues.y + diffValues.z * diffValues.z;
    auto b = 2 * (diffValues.x * (linePoints[0].x - spherePos.x) + diffValues.y * (linePoints[0].y - spherePos.y) + diffValues.z * (linePoints[0].z - spherePos.z));
    auto c = spherePos.x * spherePos.x + spherePos.y * spherePos.y + spherePos.z * spherePos.z;
    c += linePoints[0].x * linePoints[0].x + linePoints[0].y * linePoints[0].y + linePoints[0].z * linePoints[0].z;
    c -= 2 * (spherePos.x * linePoints[0].x + spherePos.y * linePoints[0].y + spherePos.z * linePoints[0].z);
    c -= sphereRadius * sphereRadius;
    auto delta = b * b - 4 * a * c;

    if (abs(a) < std::numeric_limits<float>::epsilon() || delta < 0) {
        return false; // line does not intersect
    }
    return true; // line intersects or touches the sphere
}
