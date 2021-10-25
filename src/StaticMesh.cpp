#include "StaticMesh.h"

std::array<glm::vec2, 4> StaticMesh::getQuad() {
    std::array<glm::vec2, 4> quad = {
      glm::vec2(0, 1),
      glm::vec2(0, 0),
      glm::vec2(1, 1),
      glm::vec2(1, 0)};
    return quad;
}

std::array<glm::vec3, 4> StaticMesh::getPlainVertices() {
    std::array<glm::vec3, 4> quadVertices = {
    glm::vec3(-200.0f, 0.0f, -200.0f),
    glm::vec3(-200.0f, 0.0f, 200.0f),
    glm::vec3(200.0f, 0.0f, -200.0f), 
    glm::vec3(200.0f, 0.0f, 200.0f) };
    return quadVertices;
}

std::array<glm::vec2, 4> StaticMesh::getPlainTexCoords() {
    std::array<glm::vec2, 4> quadTextCoords = {
    glm::vec2(0.0f, 20.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(20.0f, 20.0f),
    glm::vec2(20.0f, 0.0f) };
    return quadTextCoords;
}

std::array<glm::vec3, 4> StaticMesh::getPlainColors() {
    std::array<glm::vec3, 4> quadColors = {
     glm::vec3(0.0f, 0.5f, 0.0f),
    glm::vec3(0.0f, 0.85f, 0.0f),
    glm::vec3(0.0f, 0.35f, 0.25f),
    glm::vec3(0.0f, 0.8f, 0.2f) };
    return quadColors;
}