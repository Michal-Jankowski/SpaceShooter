

#include "LineCollider.h"
#include "CollisionMath.h"
#include "SphereCollider.h"

LineCollider::LineCollider(std::shared_ptr<Transform> &transformRef, Line *lineRef) : Collider(transformRef, false)  {
    this->lineRef = lineRef;
}

bool LineCollider::isColliding(Collider *other) {
    if(auto* sCol = dynamic_cast<SphereCollider*>(other)){
        return CollisionMath::LineSphereCollision(getStart(),getEnd(), sCol->transformRef->getPosition(), sCol->radius);
    }
    return false;
}

glm::vec3 LineCollider::getStart() {
    return lineRef->getStartPosition();
}

glm::vec3 LineCollider::getEnd() {
    return lineRef->getEndPosition();
}
