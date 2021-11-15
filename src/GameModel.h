//
// Created by aklin on 06.11.2021.
//

#ifndef SPACESHOOTER_GAMEMODEL_H
#define SPACESHOOTER_GAMEMODEL_H


#include "ShaderProgram.h"
#include "ModelMesh.h"
#include "Material.h"
#include "Collider.h"

class GameModel {
public:

    explicit GameModel(const std::string& path);

    void render();
    void moveBy(glm::vec3 distance);
    void rotateBy(glm::vec4 rotation);
    void scaleBy(glm::vec3 scale);

    glm::mat4 mModelMatrix;
    ShaderProgram shader;
    ModelMesh mesh = ModelMesh();

    std::unique_ptr<Collider>  col;
};


#endif //SPACESHOOTER_GAMEMODEL_H
