//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLECTIBLE_H
#define SPACESHOOTER_COLLECTIBLE_H


#include "../../engine/models/GameModel.h"
#include "../../engine/buffers/StencilOutline.h"

class Collectible : public GameModel {
public:
    explicit Collectible();
    void update(SetupWindow* gScene) override;
    void onCollision(GameObject *other) override;
    void drawHud(GameHUD *hud) override;
    bool isValidCollisionTarget(GameObject *other) const override;
private:
    inline static const std::string MODEL_PATH = "../res/models/collectible.obj";
    StencilOutline m_outline;
};


#endif //SPACESHOOTER_COLLECTIBLE_H
