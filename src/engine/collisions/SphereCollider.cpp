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

SphereCollider::SphereCollider(std::shared_ptr<Transform> &transformRef, float radius, bool drawDebug) : Collider(transformRef, drawDebug) {
    this->radius = radius;
}

void SphereCollider::drawDebugImpl() {
    Line laser = Line(glm::vec3(0), glm::vec3(0));
    for (int i = 0; i < debugResolution; ++i) {
        glm::vec3 start = MathUtils::sphericalToCartesian(radius, (float)i * (360.0f / debugResolution), 0);
        glm::vec3 end = MathUtils::sphericalToCartesian(radius, ((float)i+1.0f) * (360.0f/debugResolution), 0);
        laser.setPosition(start,end);
        laser.draw();
    }
    for (int i = 0; i < debugResolution; ++i) {
        glm::vec3 start = MathUtils::sphericalToCartesian(radius, 0, (float)i * (360.0f / debugResolution));
        glm::vec3 end = MathUtils::sphericalToCartesian(radius, 0,((float)i+1.0f) * (360.0f/debugResolution));
        laser.setPosition(start,end);
        laser.draw();
    }
    for (int i = 0; i < debugResolution; ++i) {
        glm::vec3 start = MathUtils::sphericalToCartesian(radius, 90, (float)i * (360.0f / debugResolution));
        glm::vec3 end = MathUtils::sphericalToCartesian(radius, 90,((float)i+1.0f) * (360.0f/debugResolution));
        laser.setPosition(start,end);
        laser.draw();
    }
}




