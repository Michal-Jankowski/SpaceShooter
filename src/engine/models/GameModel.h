//
// Created by aklin on 06.11.2021.
//

#ifndef SPACESHOOTER_GAMEMODEL_H
#define SPACESHOOTER_GAMEMODEL_H


#include <src/engine/core/SetupWindow.h>
#include <src/engine/shaders/ShaderProgram.h>
#include <src/engine/collisions/Collider.h>
#include "ModelMesh.h"

class GameModel {
public:

    explicit GameModel(const std::string& path,glm::vec3 pos = glm::vec3(0));

    virtual void update(SetupWindow& gScene);
    virtual void onCollision(GameModel* other);
    void render();
    void moveBy(glm::vec3 distance);
    glm::vec3 getPosition();

    ShaderProgram shader;
    ModelMesh mesh = ModelMesh();

    bool useCollision = false;
    std::unique_ptr<Collider>  col;
    bool awaitingDestroy = false;

private:
    glm::mat4 mModelMatrix;


};


#endif //SPACESHOOTER_GAMEMODEL_H
