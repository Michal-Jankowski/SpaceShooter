#ifndef SPACESHOOTER_ENEMY_H
#define SPACESHOOTER_ENEMY_H


#include "../../engine/models/GameModel.h"

class Enemy : public GameModel {
public:
    explicit Enemy(const std::string &modelPath);
    void update(SetupWindow *gScene) override;
    void onCollision(GameObject *other) override;
};


#endif //SPACESHOOTER_ENEMY_H
