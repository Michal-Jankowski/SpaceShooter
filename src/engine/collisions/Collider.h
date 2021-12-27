//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLIDER_H
#define SPACESHOOTER_COLLIDER_H

#include <glm/vec3.hpp>
#include <memory>
#include "../models/Transform.h"

class Collider {
public:
    explicit Collider(std::shared_ptr<Transform> &transformRef, bool drawDebug);

    virtual bool isColliding(Collider* other) =0;
    //TODO: BB fast check
    void drawDebug();
    bool debugEnable;
    std::shared_ptr<Transform> transformRef;
protected:
    virtual void drawDebugImpl() = 0;

private:


};


#endif //SPACESHOOTER_COLLIDER_H
