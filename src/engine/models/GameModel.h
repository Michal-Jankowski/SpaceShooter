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
    explicit GameModel(SetupWindow* scene, const std::string& path, glm::vec3 position = glm::vec3(0));
    void render() override;
    void drawHud(HUD *hud) override {}
    void reinit() override;
    bool isValidCollisionTarget(GameObject *other) const override {return false;}
    std::unique_ptr<Transform> transform;

    ModelMesh mesh = ModelMesh();
    ShaderProgram shader;
};


#endif //SPACESHOOTER_GAMEMODEL_H
