//
// Created by aklin on 15.11.2021.
//

#include <glm/vec3.hpp>
#include <glm/exponential.hpp>
#include "SphereCollider.h"

bool SphereCollider::isColliding(Collider* other) {
    if(SphereCollider* sCol = dynamic_cast<SphereCollider*>(other)){
        glm::vec3 diff = pos - sCol->pos;
        glm::vec3 sq = glm::vec3(diff.x*diff.x, diff.y*diff.y, diff.z*diff.z);
        float dist = glm::sqrt(sq.x+sq.y+sq.z);
        return dist < sCol->radius + radius;
    }
    return false;
}
