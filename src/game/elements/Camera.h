#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <GLFW/glfw3.h>
class Camera
{
public:
	Camera(const glm::vec3& pos, const glm::vec3& viewPoint, const glm::vec3& up, glm::i32vec2 windowPosition, float moveSpeed = 5.0f, float mouseSensitivity = 0.1f);
	void update(std::function<bool(int)> input,  glm::i32vec2 getCursorPos,  std::function<void(glm::i32vec2&)> setCursor,
		std::function<float(float)> speedOffset);
	[[nodiscard]] glm::vec3 getNormalizedViewVector() const;
	[[nodiscard]] glm::mat4 getViewMatrix() const;
	[[nodiscard]] glm::vec3 getEye() const;
    void returnToInitPosition();
private:
	void flyBy(float distance);
	void strafeBy(float distance);
	void moveVertical(float angleInDegrees);
	void moveHorizontal(float angleInDegrees);

	glm::vec3 m_position;
	glm::vec3 m_viewPoint;
	glm::vec3 m_upVector;
    glm::vec3 init_pos;
    glm::vec3 init_viewPoint;
    glm::vec3 init_upVector;

	float m_mouseSensitivity;
	float m_moveSpeed;

	glm::i32vec2 m_windowCenterPosition;
};

