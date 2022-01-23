#include <glm/vec3.hpp>
#include <glm/exponential.hpp>
#include "SphereCollider.h"
#include "LineCollider.h"
#include "CollisionMath.h"
#include "../utils/MathUtils.h"

bool SphereCollider::isColliding(Collider* other) {
    if(auto* sCol = dynamic_cast<SphereCollider*>(other)){
        glm::vec3 diff = transformRef->getPosition() - sCol->transformRef->getPosition();
        glm::vec3 sq = glm::vec3(diff.x*diff.x, diff.y*diff.y, diff.z*diff.z);
        float dist = glm::sqrt(sq.x+sq.y+sq.z);
        return dist < sCol->radius + radius;
    } else if(auto* lCol = dynamic_cast<LineCollider*>(other)){
        return CollisionMath::lineSphereCollision(lCol->getStart(), lCol->getEnd(), transformRef->getPosition(), radius);
    }
    return false;
}

SphereCollider::SphereCollider(Transform* transformRef, float radius, bool drawDebug) : Collider(transformRef, drawDebug) {
    this->radius = radius;
}

void SphereCollider::drawDebugInternal(Line& laser, float radius,  float phi1, float phi2, float theta1, float theta2) {
    glm::vec3 start = MathUtils::sphericalToCartesianAngles(radius, phi1, theta1);
    glm::vec3 end = MathUtils::sphericalToCartesianAngles(radius, phi2, theta2);
    std::vector<glm::vec3> laserPoints{ start + transformRef->getPosition(), end + transformRef->getPosition() };
    laser.setPosition(laserPoints);
    laser.draw();
}

void SphereCollider::drawDebugImpl() {
    Line laser = Line(glm::vec3(0), glm::vec3(0));
    laser.setColor(glm::vec4(0.2f, 0.85f, 0.1f, 0.0f));
    for (auto i = 0; i < debugResolution; ++i) {
        auto phi1 = (float)i * (360.0f / debugResolution), phi2 = ((float)i + 1.0f) * (360.0f / debugResolution);
        auto theta1 = 90, theta2 = 90;
        drawDebugInternal(laser, radius, phi1, phi2, theta1, theta2);
    }
    for (auto i = 0; i < debugResolution; ++i) {
        auto phi1 = 0, phi2 = 0;
        auto theta1 = (float)i * (180.0f / debugResolution), theta2 = ((float)i + 1.0f)* (180.0f / debugResolution);
        drawDebugInternal(laser, radius, phi1, phi2, theta1, theta2);

        phi1 = 180, phi2 = 180;
        theta1 = (float)i * (180.0f / debugResolution), theta2 = ((float)i + 1.0f)* (180.0f / debugResolution);
        drawDebugInternal(laser, radius, phi1, phi2, theta1, theta2);

    }
    for (auto i = 0; i < debugResolution; ++i) {
        auto phi1 = 90, phi2 = 90;
        auto theta1 = (float)i * (180.0f / debugResolution), theta2 = ((float)i + 1.0f) * (180.0f / debugResolution);
        drawDebugInternal(laser, radius, phi1, phi2, theta1, theta2);

        phi1 = 270, phi2 = 270;
        theta1 = (float)i * (180.0f / debugResolution), theta2 = ((float)i + 1.0f) * (180.0f / debugResolution);
        drawDebugInternal(laser, radius, phi1, phi2, theta1, theta2);
    }
}




