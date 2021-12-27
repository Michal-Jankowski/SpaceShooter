

#ifndef SPACESHOOTER_PLANET_H
#define SPACESHOOTER_PLANET_H

#include "../../engine/models/GameModel.h"

class Planet : public GameModel{
public:
    explicit Planet(float size, SetupWindow* scene);
    void update(SetupWindow* scene) override;
    void onCollision(GameObject *other) override;
private:
    inline static const std::string MODEL_PATH = "../res/models/planet.obj";
    int maxEnemies = 100;
    int maxCollectibles = 100;
};


#endif //SPACESHOOTER_PLANET_H
