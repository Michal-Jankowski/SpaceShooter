//
// Created by aklin on 06.11.2021.
//

#ifndef SPACESHOOTER_GAMEMODEL_H
#define SPACESHOOTER_GAMEMODEL_H


#include <string>
#include "../core/SetupWindow.h"
#include "../shaders/ShaderProgram.h"
#include "ModelMesh.h"
#include "../collisions/Collider.h"
#include "Transform.h"

class GameModel {
public:

    explicit GameModel(const std::string& path);
    virtual void update(SetupWindow& gScene);
    virtual void onCollision(GameModel* other);
    void render();

    ShaderProgram shader;
    ModelMesh mesh = ModelMesh();

    bool useCollision = false;
    std::unique_ptr<Collider>  col;
    bool awaitingDestroy = false;

    std::shared_ptr<Transform> transform;


};


#endif //SPACESHOOTER_GAMEMODEL_H
