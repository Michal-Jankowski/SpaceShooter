

#ifndef SPACESHOOTER_COLLISIONHANDLER_H
#define SPACESHOOTER_COLLISIONHANDLER_H


#include "../models/GameObject.h"

class CollisionHandler {
public:
    void registerCollider(GameObject* go);
    void deregisterCollider(GameObject* go);
    void runCollisionChecks();
private:
    std::vector<GameObject*> colliders;

};


#endif //SPACESHOOTER_COLLISIONHANDLER_H
