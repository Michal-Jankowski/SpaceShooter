//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_SHIP_H
#define SPACESHOOTER_SHIP_H


#include "../../engine/models/GameModel.h"
#include "../elements/Camera.h"
#include <GLFW/glfw3.h>
#include <string>


class Ship : public GameModel {
public:
    explicit Ship(std::shared_ptr<Camera> cameraRef);
    void update(SetupWindow* scene) override;
    void drawHud(GameHUD *hud) override;
    bool isValidCollisionTarget(GameObject *other) const override;

    enum PointType { enemyPoint, collectiblePoint };
    void addPoint(PointType type);
private:
    inline static const std::string MODEL_PATH = "../res/models/ship.obj";

    void shootCheck(SetupWindow* scene);
    std::shared_ptr<Camera> m_camera;
    float distCamOffset = 5.0f;
    float laserLength = 10.0f;
    float laserLifetime = 0.5f;
    float laserSpeedStartCompensation = 6.0f;
    float shootTimeout = 0.25f;
    float shootTimer = 0.0f;
    glm::vec3 heightCamOffset = glm::vec3(0.0f, -2.0f, 0.0f);
    int m_shootMouseKeyCode = GLFW_MOUSE_BUTTON_LEFT;

    int enemiesShot = 0;
    int collectiblesFound = 0;
};


#endif //SPACESHOOTER_SHIP_H
