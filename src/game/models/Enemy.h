#ifndef SPACESHOOTER_ENEMY_H
#define SPACESHOOTER_ENEMY_H


#include "../../engine/models/GameModel.h"
#include "../elements/Laser.h"

class Enemy : public GameModel {
public:
    explicit Enemy(SetupWindow* scene);
    void update() override;
    void onCollision(GameObject *other) override;
    void drawHud(GameHUD *hud) override;
    bool isValidCollisionTarget(GameObject *other) const override;
private:
    inline static const std::string MODEL_PATH = "../res/models/enemy.obj";
};


#endif //SPACESHOOTER_ENEMY_H
