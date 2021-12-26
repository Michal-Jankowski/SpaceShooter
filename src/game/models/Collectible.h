//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLECTIBLE_H
#define SPACESHOOTER_COLLECTIBLE_H


#include "../../engine/models/GameModel.h"

class Collectible : public GameModel {
public:
    explicit Collectible(const std::string& path);
    void update(SetupWindow* gScene) override;
    void onCollision(GameObject *other) override;
};


#endif //SPACESHOOTER_COLLECTIBLE_H
