

#ifndef SPACESHOOTER_PLANET_H
#define SPACESHOOTER_PLANET_H

#include "../../engine/models/GameModel.h"

class Planet : public GameModel 
{
public:
    explicit Planet(float size, SetupWindow* scene, const glm::vec3& position = glm::vec3(0));
    void update(SetupWindow* scene) override;
    void onCollision(GameObject* other) override;
    bool isValidCollisionTarget(GameObject* other) const override;
private:
    inline static const std::string MODEL_PATH = "../res/models/planet.obj";
    int enemies = 10;
    int maxCollectibles = 10;
};


#endif //SPACESHOOTER_PLANET_H
