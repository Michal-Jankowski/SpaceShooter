//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_SHIP_H
#define SPACESHOOTER_SHIP_H


#include "../../engine/models/GameModel.h"

class Ship : public GameModel {
public:
    explicit Ship(const std::string &modelPath);
    void update(SetupWindow& scene) override;
private:
    //std::unique_ptr<Camera> camera;
};


#endif //SPACESHOOTER_SHIP_H
