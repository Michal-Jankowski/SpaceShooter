

#ifndef SPACESHOOTER_LASER_H
#define SPACESHOOTER_LASER_H

#include "../../engine/buffers/Line.h"
#include "../../engine/models/GameObject.h"

class Laser : public GameObject {

public:
    Laser(glm::vec3 from, glm::vec3 to, float lifetime, GameObject* shotFrom);
    void update(SetupWindow *gScene) override;
    void render() override;
    bool isValidCollisionTarget(GameObject *other) const override;
    GameObject* getShooter();
private:
    GameObject* shotFrom;
    Line line;
    float timer;
    float speed = 500.0f;
    float lineCollisionCheckLength = 1000.0f;
};


#endif //SPACESHOOTER_LASER_H
