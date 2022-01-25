#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

constexpr auto forwardKeyCode = GLFW_KEY_W;
constexpr auto backwarKeyCode = GLFW_KEY_S;
constexpr auto strafeLeftKeyCode = GLFW_KEY_A;
constexpr auto strafeRightKeyCode = GLFW_KEY_D;
constexpr auto accelerateKeyCode = GLFW_KEY_LEFT_SHIFT;
constexpr auto accelerateSpeed = 5.0f;
constexpr auto maxRotationAngle = 85.0f;
Camera::Camera(const glm::vec3& pos, const glm::vec3& viewPoint, const glm::vec3& up, glm::i32vec2 windowPosition, float moveSpeed, float mouseSensitivity)
  :  m_position(pos)
  ,  init_pos(pos)
  ,  m_viewPoint(viewPoint)
  ,  init_viewPoint(viewPoint)
  ,  m_upVector(up)
  ,  init_upVector(up)
  ,  m_moveSpeed(moveSpeed)
  ,  m_mouseSensitivity(mouseSensitivity)
  ,  m_windowCenterPosition(windowPosition)
{
}

void Camera::returnToInitPosition() {
    m_position = init_pos;
    m_viewPoint = init_viewPoint;
    m_upVector = init_upVector;
}

void Camera::update(const std::function<bool(int)>& keyInputFunc, const glm::i32vec2& getCursorPos, const std::function<void(const glm::i32vec2&)>& setCursorPosFunc,
	const std::function<float(float)>& speedCorrectionFunc)
{
	flyBy(speedCorrectionFunc(m_moveSpeed));

	if (keyInputFunc(accelerateKeyCode)) {
		flyBy(speedCorrectionFunc(accelerateSpeed * m_moveSpeed));
	}
	if (keyInputFunc(backwarKeyCode)) {
		flyBy(speedCorrectionFunc(-m_moveSpeed));
	}
	if (keyInputFunc(strafeLeftKeyCode)) {
		strafeBy(speedCorrectionFunc(-m_moveSpeed));
	}
	if (keyInputFunc(strafeRightKeyCode)) {
		strafeBy(speedCorrectionFunc(m_moveSpeed));
	}
	const auto& currentMousePosition = getCursorPos;
	const auto& delta = m_windowCenterPosition - currentMousePosition;

	if (delta.x != 0) {
		rotateLeftRight(static_cast<float>(delta.x) * m_mouseSensitivity);
	}
	if (delta.y != 0) {
		rotateUpDown(static_cast<float>(delta.y) * m_mouseSensitivity);
	}
	setCursorPosFunc(m_windowCenterPosition);
}

glm::vec3 Camera::getNormalizedViewVector() const {
	return glm::normalize(m_viewPoint - m_position);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_position, m_viewPoint, m_upVector);
}

glm::vec3 Camera::getEye() const {
	return m_position;
}

void Camera::flyBy(float distance) {
	glm::vec3 offset = getNormalizedViewVector();
	offset *= distance;
	m_position += offset;
	m_viewPoint += offset;
}

void Camera::strafeBy(float distance) {
	glm::vec3 strafeVector = glm::normalize(glm::cross(getNormalizedViewVector(), m_upVector));
	strafeVector = glm::normalize(strafeVector) * distance;
	m_position += strafeVector;
	m_viewPoint += strafeVector;
}

void Camera::rotateLeftRight(float degrees) {
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);
	m_viewPoint = m_position + glm::vec3(rotatedViewVector);
}

void Camera::rotateUpDown(float degrees) {
	const auto& viewVec = getNormalizedViewVector();
	const auto& viewVecXZ = glm::normalize(glm::vec3(viewVec.x, 0.0f, viewVec.z));

	auto currentAngleDegrees = glm::degrees(acos(glm::dot(viewVecXZ, viewVec)));
	if (viewVec.y < 0.0f) {
		currentAngleDegrees = -currentAngleDegrees;
	}

	auto newAngleDegrees = currentAngleDegrees + degrees;
	if (newAngleDegrees > -maxRotationAngle && newAngleDegrees < maxRotationAngle) {
		glm::vec3 rotationAxis = glm::normalize(glm::cross(getNormalizedViewVector(), m_upVector));

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), rotationAxis);
		glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);

		m_viewPoint = m_position + glm::vec3(rotatedViewVector);
	}
}


