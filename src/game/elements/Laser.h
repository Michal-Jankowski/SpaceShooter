

#ifndef SPACESHOOTER_LASER_H
#define SPACESHOOTER_LASER_H

#include "../../engine/buffers/Line.h"
#include "../../engine/models/GameObject.h"

class Laser : public GameObject {

public:
    Laser(SetupWindow *scene, glm::vec3 from, glm::vec3 to, float lifetime, GameObject* shotFrom);
    void update() override;
    void render() override;
    bool isValidCollisionTarget(GameObject *other) const override;
    GameObject* getShooter();

    constexpr static const float laserLength = 10.0f;
    constexpr static float laserLifetime = 0.5f;
    constexpr static float laserSpeedStartCompensation = 6.0f;

private:
    GameObject* shotFrom;
    Line line;
    float timer;
    float speed = 500.0f;
    float lineCollisionCheckLength = 1000.0f;
};


#endif //SPACESHOOTER_LASER_H
