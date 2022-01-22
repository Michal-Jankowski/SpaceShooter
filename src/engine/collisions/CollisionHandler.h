

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
    void setBufferLineParams(glm::vec3 start, glm::vec3 end, glm::vec3 col);
    std::vector<GameObject*> colliders;
    static const int debugLineBufferSize = 5;
    glm::vec3 lineBuffer [debugLineBufferSize][3];
    int debugLineCounter = 0;

    constexpr static const glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f);
    constexpr static const glm::vec3 greenColor = glm::vec3(0.0f, 1.0f, 0.0f);
};


#endif //SPACESHOOTER_COLLISIONHANDLER_H
