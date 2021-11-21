//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLIDER_H
#define SPACESHOOTER_COLLIDER_H

#include <glm/vec3.hpp>

class Collider {
public:
    explicit Collider(bool drawDebug);

    virtual bool isColliding(Collider* other) =0;
    void drawDebug();
    glm::vec3 pos;
    bool debugEnable;

protected:
    virtual void drawDebugImpl() = 0;
private:


};


#endif //SPACESHOOTER_COLLIDER_H
