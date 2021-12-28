#ifndef SPACESHOOTER_ENEMY_H
#define SPACESHOOTER_ENEMY_H


#include "../../engine/models/GameModel.h"

class Enemy : public GameModel {
public:
    explicit Enemy();
    void update(SetupWindow *gScene) override;
    void onCollision(GameObject *other) override;
    void drawHud(GameHUD *hud) override;
private:
    inline static const std::string MODEL_PATH = "../res/models/enemy.obj";
};


#endif //SPACESHOOTER_ENEMY_H
