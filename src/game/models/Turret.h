

#ifndef SPACESHOOTER_TURRET_H
#define SPACESHOOTER_TURRET_H


#include "Enemy.h"
#include "../GameScene.h"

class Turret : public Enemy {
public:
    Turret(SetupWindow* scene);
    void update() override;
    void drawHud(GameHUD *hud) override;
    void renderDebug() override;
private:
    const float shootAttemptInterval = 4.0f;
    float randomShootInterval;
    float shootAttemptTimer = 0.0f;
    float shootRandomSize = 10.0f;
    void tryShoot(GameScene *gScene);
    static bool isSightInterruptor(GameObject* go);
    inline static const std::string MODEL_PATH = "../res/models/enemy.obj";

    constexpr static const glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f);
    constexpr static const glm::vec3 greenColor = glm::vec3(0.0f, 1.0f, 0.0f);
};


#endif //SPACESHOOTER_TURRET_H
