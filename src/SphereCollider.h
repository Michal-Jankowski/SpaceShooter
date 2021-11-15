//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_SPHERECOLLIDER_H
#define SPACESHOOTER_SPHERECOLLIDER_H


#include "Collider.h"

class SphereCollider : Collider {

public:
    bool isColliding(Collider* other) override;
    glm::vec3 pos;
    float radius;

};


#endif //SPACESHOOTER_SPHERECOLLIDER_H
