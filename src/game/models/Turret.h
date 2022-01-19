

#ifndef SPACESHOOTER_TURRET_H
#define SPACESHOOTER_TURRET_H


#include "Enemy.h"

class Turret : public Enemy {

    void update(SetupWindow *gScene) override;
private:
    inline static const std::string MODEL_PATH = "../res/models/enemy.obj";
};


#endif //SPACESHOOTER_TURRET_H
