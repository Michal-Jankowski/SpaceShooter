#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <GLFW/glfw3.h>
class Camera
{
public:
	Camera(const glm::vec3& pos, const glm::vec3& viewPoint, const glm::vec3& up, glm::i32vec2 windowPosition, float moveSpeed = 5.0f, float mouseSensitivity = 0.1f);
	void setKeyboardControls(int forwardKeyCode, int backwardKeyCode, int strafeLeftKeyCode, int strafeRightKeyCode);
	void update(const std::function<bool(int)>& keyInputFunc, const std::function<glm::i32vec2()>& getCursorPosFunc, const std::function<void(const glm::i32vec2&)>& setCursorPosFunc,
		const std::function<float(float)>& speedCorrectionFunc);
	void setWindowCenterPosition(const glm::i32vec2& windowCenterPosition);
	[[nodiscard]] glm::vec3 getNormalizedViewVector() const;
	[[nodiscard]] glm::mat4 getViewMatrix() const;
	[[nodiscard]] glm::vec3 getEye() const;
	[[nodiscard]] glm::vec3  getViewPoint() const;
    void returnToInitPosition();
private:
	void moveBy(float distance);
	void strafeBy(float distance);
	void rotateLeftRight(float angleInDegrees);
	void rotateUpDown(float angleInDegrees);

	glm::vec3 m_position;
	glm::vec3 m_viewPoint;
	glm::vec3 m_upVector;

    glm::vec3 init_pos;
    glm::vec3 init_viewPoint;
    glm::vec3 init_upVector;

	float m_mouseSensitivity;
	float m_moveSpeed;
	int m_forwardKeyCode = GLFW_KEY_W;
	int m_backwarKeyCode = GLFW_KEY_S;
	int m_strafeLeftKeyCode = GLFW_KEY_A;
	int m_strafeRightKeyCode = GLFW_KEY_D;
	int m_accelerateKeyCode = GLFW_KEY_LEFT_SHIFT;

	glm::i32vec2 m_windowCenterPosition;
};

