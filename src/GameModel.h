//
// Created by aklin on 06.11.2021.
//

#ifndef SPACESHOOTER_GAMEMODEL_H
#define SPACESHOOTER_GAMEMODEL_H


#include "ShaderProgram.h"
#include "ModelMesh.h"

class GameModel {
public:

    GameModel(std::string path, std::string shaderKey);

    void Render();
    void MoveBy(glm::vec3 distance);
    void RotateBy(glm::vec4 rotation);
    void ScaleBy(glm::vec3 scale);

    glm::mat4 mModelMatrix;
    ShaderProgram shader;
    ModelMesh mesh;
};


#endif //SPACESHOOTER_GAMEMODEL_H
