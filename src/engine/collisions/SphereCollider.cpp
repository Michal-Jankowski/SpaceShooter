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

SphereCollider::SphereCollider( float radius, bool drawDebug = false) : Collider(drawDebug) {
    this->radius = radius;
}

void SphereCollider::drawDebugImpl() {
    for (int i = 0; i < debugResolution; ++i) {
        Laser laser = Laser(spherePoint((float)i * (360.0f/debugResolution), 0),
                            spherePoint(((float)i+1.0f) * (360.0f/debugResolution), 0));
        laser.draw();
    }
    for (int i = 0; i < debugResolution; ++i) {
        Laser laser = Laser(spherePoint(0, (float)i * (360.0f/debugResolution)),
                            spherePoint(0,((float)i+1.0f) * (360.0f/debugResolution)));
        laser.draw();
    }
    for (int i = 0; i < debugResolution; ++i) {
        Laser laser = Laser(spherePoint(90, (float)i * (360.0f/debugResolution)),
                            spherePoint(90,((float)i+1.0f) * (360.0f/debugResolution)));
        laser.draw();
    }


}


glm::vec3 SphereCollider::spherePoint(float phi, float theta) {
    return glm::vec3(
            cos(theta * PI / 180.0) * cos(phi * PI / 180.0),
            cos(theta * PI / 180.0) * sin(phi * PI / 180.0),
            sin(theta * PI / 180.0)
    ) * radius;
}



