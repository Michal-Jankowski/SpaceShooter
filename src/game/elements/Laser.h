

#ifndef SPACESHOOTER_LASER_H
#define SPACESHOOTER_LASER_H

#include "../../engine/buffers/Line.h"
#include "../../engine/models/GameObject.h"

class Laser : public GameObject {

public:
    Laser(glm::vec3 from, glm::vec3 to, float lifetime);
    void update(SetupWindow *gScene) override;
    void render() override;

private:
    Line line;
    float timer;

};


#endif //SPACESHOOTER_LASER_H
