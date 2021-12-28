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
#include "GameObject.h"

class GameModel : public GameObject {
public:

    explicit GameModel(const std::string& path, glm::vec3 position = glm::vec3(0));
    void render() override;
    void drawHud(GameHUD *hud) override {}


    ShaderProgram shader;
    ModelMesh mesh = ModelMesh();

    std::unique_ptr<Transform> transform;

};


#endif //SPACESHOOTER_GAMEMODEL_H
