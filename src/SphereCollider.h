#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"
#include "Laser.h"

#define PI 3.14159265

class SphereCollider : public Collider {

public:
    SphereCollider(float radius, bool drawDebug);
    bool isColliding(Collider* other) override;
    void drawDebugImpl() override;
    float radius;

private:
    static const int debugResolution = 50;
    glm::vec3 spherePoint(float phi, float theta);
};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
