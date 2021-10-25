#include "StaticMesh.h"

std::vector<glm::vec2> StaticMesh::getQuad() {
    std::vector<glm::vec2> quad = {
      glm::vec2(0, 1),
      glm::vec2(0, 0),
      glm::vec2(1, 1),
      glm::vec2(1, 0)};
    return quad;
}

std::vector<glm::vec3> StaticMesh::getPlainVertices() {
    std::vector<glm::vec3> quadVertices = {
    glm::vec3(-200.0f, 0.0f, -200.0f),
    glm::vec3(-200.0f, 0.0f, 200.0f),
    glm::vec3(200.0f, 0.0f, -200.0f), 
    glm::vec3(200.0f, 0.0f, 200.0f) };
    return quadVertices;
}

std::vector<glm::vec2> StaticMesh::getPlainTexCoords() {
    std::vector<glm::vec2> quadTextCoords = {
    glm::vec2(0.0f, 20.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(20.0f, 20.0f),
    glm::vec2(20.0f, 0.0f) };
    return quadTextCoords;
}

std::vector<glm::vec3> StaticMesh::getPlainColors() {
    std::vector<glm::vec3> quadColors = {
     glm::vec3(0.0f, 0.5f, 0.0f),
    glm::vec3(0.0f, 0.85f, 0.0f),
    glm::vec3(0.0f, 0.35f, 0.25f),
    glm::vec3(0.0f, 0.8f, 0.2f) };
    return quadColors;
}