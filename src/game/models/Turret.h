

#ifndef SPACESHOOTER_TURRET_H
#define SPACESHOOTER_TURRET_H


#include "Enemy.h"
#include "../GameScene.h"

class Turret : public Enemy {
public:
    Turret(SetupWindow* scene);
    void update() override;
    void drawHud(GameHUD *hud) override;
private:
    const float shootAttemptInterval = 1.0f;
    float shootAttemptTimer = 0.0f;
    float shootRandomSize = 10.0f;
    void tryShoot(GameScene *gScene);
    static bool isSightInterruptor(GameObject* go);
    inline static const std::string MODEL_PATH = "../res/models/enemy.obj";
};


#endif //SPACESHOOTER_TURRET_H
