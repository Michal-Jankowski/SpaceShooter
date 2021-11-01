#include "MatrixManager.h"

MatrixManager& MatrixManager::getInstance() {
    static MatrixManager matrixManager;
    return matrixManager;
}

const glm::mat4& MatrixManager::getProjectionMatrix() const {
    return m_projectionMatrix;
}

const glm::mat4& MatrixManager::getOrthoProjectionMatrix() const {
    return m_orthoProjectionMatrix;
}

const glm::mat4& MatrixManager::getViewMatrix() const {
    return m_viewMatrix;
}

void MatrixManager::setProjectionMatrix(const glm::mat4& projectionMatrix) {
    m_projectionMatrix = projectionMatrix;
}

void MatrixManager::setOrthoProjectionMatrix(const glm::mat4& orthoProjectionMatrix) {
    m_orthoProjectionMatrix = orthoProjectionMatrix;
}

void MatrixManager::setViewMatrix(const glm::mat4& viewMatrix) {
    m_viewMatrix = viewMatrix;
}