#ifndef SPACESHOOTER_SHIP_H
#define SPACESHOOTER_SHIP_H


#include "../../engine/models/GameModel.h"
#include "../elements/Camera.h"
#include <GLFW/glfw3.h>
#include <string>


class Ship : public GameModel {
public:
    Ship(SetupWindow* scene, std::shared_ptr<Camera> cameraRef);
    void update() override;
    void drawHud(HUD *hud) override;
    bool isValidCollisionTarget(GameObject *other) const override;
    void onCollision(GameObject* other) override;
    void reinit() override;

    enum PointType { enemyPoint, collectiblePoint };
    void addPoint(PointType type);
    void damage(bool autoKill = false);
    void addTotalTarget(int enemies, int collectibles);
private:
    inline static const std::string MODEL_PATH = "../res/models/ship.obj";

    void init();
    void shootCheck();
    std::shared_ptr<Camera> m_camera;
    float distCamOffset = 5.0f;

    float laserDmgChance = 0.3f;
    float shootTimeout = 0.25f;
    float shootTimer = 0.0f;
    glm::vec3 heightCamOffset = glm::vec3(0.0f, -2.0f, 0.0f);
    int m_shootMouseKeyCode = GLFW_MOUSE_BUTTON_LEFT;

    int lives = 0;
    const int initLives = 15;
    int enemiesShot = 0;
    int totalEnemies = 0;
    int collectiblesFound = 0;
    int totalCollectibles = 0;

};


#endif //SPACESHOOTER_SHIP_H
