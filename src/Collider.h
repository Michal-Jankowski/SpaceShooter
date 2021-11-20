//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLIDER_H
#define SPACESHOOTER_COLLIDER_H

#include <glm/vec3.hpp>

class Collider {
public:
    virtual bool isColliding(Collider* other) =0;
    glm::vec3 pos;
};


#endif //SPACESHOOTER_COLLIDER_H
