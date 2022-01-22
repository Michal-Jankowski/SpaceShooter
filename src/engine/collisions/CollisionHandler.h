

#ifndef SPACESHOOTER_COLLISIONHANDLER_H
#define SPACESHOOTER_COLLISIONHANDLER_H


#include "../models/GameObject.h"
#include "../models/GameModel.h"
#include "../buffers/Line.h"

class CollisionHandler {
public:
    CollisionHandler();
    void registerCollider(GameObject* go);
    void deregisterCollider(GameObject* go);
    void runCollisionChecks();
    void drawDebug();
    bool inLineOfSight(const GameModel &go1, const GameModel & go2, bool (*obstacle)(GameObject*));
private:
    std::vector<GameObject*> colliders;
};


#endif //SPACESHOOTER_COLLISIONHANDLER_H
