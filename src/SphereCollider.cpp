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

SphereCollider::SphereCollider(glm::vec3 pos, float radius, bool drawDebug = false) : Collider(drawDebug) {
    this->pos = pos;
    this->radius = radius;
}

void SphereCollider::drawDebugImpl() {
    for (int i = 0; i < debugResolution; ++i) {
        //theta == 0; phi == 0 -> 360
        //laser.startPoint = spherePoint(0, (float)i * (360.0f/debugResolution));

        //laser.endPoint = spherePoint(0, ((float)i+1.0f) * (360.0f/debugResolution));
        Laser laser = Laser(spherePoint(0, (float)i * (360.0f/debugResolution)),
                            spherePoint(0, ((float)i+1.0f) * (360.0f/debugResolution)));
        laser.draw();
//
//        std::cout   << laser.startPoint.x << " "
//                    << laser.startPoint.y << " "
//                    << laser.startPoint.z << " "
//                    << laser.endPoint.x << " "
//                    << laser.endPoint.y << " "
//                    << laser.endPoint.z << std::endl;
    }
}


glm::vec3 SphereCollider::spherePoint(float phi, float theta) {
    return glm::vec3(
            cos(theta * PI / 180.0) * cos(phi * PI / 180.0),
            cos(theta * PI / 180.0) * sin(phi * PI / 180.0),
            sin(theta * PI / 180.0)
    ) * radius + pos;
}



