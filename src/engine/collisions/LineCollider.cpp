

#include "LineCollider.h"
#include "CollisionMath.h"
#include "SphereCollider.h"

LineCollider::LineCollider(std::shared_ptr<Transform> &transformRef, const glm::vec3 &lineStart, const glm::vec3 &lineEnd)
                           : Collider(transformRef, false),
                           lineStart(lineStart), lineEnd(lineEnd){

}

bool LineCollider::isColliding(Collider *other) {
    if(auto* sCol = dynamic_cast<SphereCollider*>(other)){
        return CollisionMath::lineSphereCollision(getStart(), getEnd(), sCol->transformRef->getPosition(), sCol->radius);
    }
    return false;
}

glm::vec3 LineCollider::getStart() {
    return lineStart;
}

glm::vec3 LineCollider::getEnd() {
    return lineEnd;
}


