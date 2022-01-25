#ifndef SPACESHOOTER_ENEMY_H
#define SPACESHOOTER_ENEMY_H


#include "../../engine/models/GameModel.h"
#include "../elements/Laser.h"

class Enemy : public GameModel {
public:
    Enemy(SetupWindow* scene);
    Enemy(SetupWindow* scene, const std::string &model_path);
    void update() override;
    void onCollision(GameObject *other) override;
    bool isValidCollisionTarget(GameObject *other) const override;
private:
    inline static const std::string MODEL_PATH = "../res/models/mine.obj";
};


#endif //SPACESHOOTER_ENEMY_H
