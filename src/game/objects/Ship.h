//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_SHIP_H
#define SPACESHOOTER_SHIP_H


#include "../../engine/models/GameModel.h"
#include "Camera.h"

class Ship : public GameModel {
public:
    explicit Ship(const std::string &modelPath, std::shared_ptr<Camera> &cameraRef);
    void update(SetupWindow& scene) override;
private:
    std::shared_ptr<Camera> cameraRef;
    float distCamOffset = 5.0f;
    glm::vec3 heightCamOffset = glm::vec3(0.0f, -2.0f, 0.0f);
};


#endif //SPACESHOOTER_SHIP_H
