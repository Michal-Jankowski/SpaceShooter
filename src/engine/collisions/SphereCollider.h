#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"



class SphereCollider : public Collider {

public:
    explicit SphereCollider(Transform* transformRef, float radius = 1.0f);
    bool isColliding(Collider* other) override;

    [[nodiscard]] const float getScaledRadius();
private:
    static const int debugResolution = 25;
    void drawDebugImpl() override;
    void drawDebugInternal(Line& laser, float radius, float phi1, float phi2, float theta1, float theta2);
    float rawRadius;
};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
