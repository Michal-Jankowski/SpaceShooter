#pragma once

#include <glm/glm.hpp>

class MatrixManager
{
public:
	static MatrixManager& getInstance();
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getOrthoProjectionMatrix() const;
	const glm::mat4& getViewMatrix() const;
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	void setOrthoProjectionMatrix(const glm::mat4& orthoProjectionMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
private:
	MatrixManager() { m_projectionMatrix = glm::mat4(0), m_orthoProjectionMatrix = glm::mat4(0), m_viewMatrix = glm::mat4(0); }
	MatrixManager(const MatrixManager&) = delete;
	void operator=(const MatrixManager&) = delete;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_orthoProjectionMatrix;
	glm::mat4 m_viewMatrix;

};

