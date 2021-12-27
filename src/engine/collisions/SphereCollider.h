#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"

#define PI 3.14159265

class SphereCollider : public Collider {

public:
    SphereCollider(std::shared_ptr<Transform> &transformRef, float radius, bool drawDebug);
    bool isColliding(Collider* other) override;

    float radius;
private:
    static const int debugResolution = 20;
    glm::vec3 spherePoint(float phi, float theta);
    void drawDebugImpl() override;
};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
