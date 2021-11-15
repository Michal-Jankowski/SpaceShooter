//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLIDER_H
#define SPACESHOOTER_COLLIDER_H

class Collider {
public:
    virtual bool isColliding(Collider* other) =0;
};


#endif //SPACESHOOTER_COLLIDER_H
