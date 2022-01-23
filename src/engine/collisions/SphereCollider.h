#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"



class SphereCollider : public Collider {

public:
    SphereCollider(Transform* transformRef, float radius, bool drawDebug);
    bool isColliding(Collider* other) override;

    float radius;
private:
    static const int debugResolution = 25;
    void drawDebugImpl() override;
    void drawDebugInternal(Line& laser, float radius, float phi1, float phi2, float theta1, float theta2);
};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
