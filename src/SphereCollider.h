//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"

class SphereCollider : public Collider {

public:
    SphereCollider(glm::vec3 pos, float radius);
    bool isColliding(Collider* other) override;

    float radius;

};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
