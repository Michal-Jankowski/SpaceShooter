#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"



class SphereCollider : public Collider {

public:
    SphereCollider(std::shared_ptr<Transform> &transformRef, float radius, bool drawDebug);
    bool isColliding(Collider* other) override;

    float radius;
private:
    static const int debugResolution = 20;
    void drawDebugImpl() override;
};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
