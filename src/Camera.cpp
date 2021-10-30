#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(const glm::vec3& pos, const glm::vec3& viewPoint, const glm::vec3& up,float moveSpeed, float mouseSensitivity)
  :  m_position(pos)
  ,  m_viewPoint(viewPoint)
  ,  m_upVector(up)
  ,  m_moveSpeed(moveSpeed)
  ,  m_mouseSensitivity(mouseSensitivity)
{
}

void Camera::setKeyboardControls(int forwardKeyCode, int backwardKeyCode, int strafeLeftKeyCode, int strafeRightKeyCode) {
	m_forwardKeyCode = forwardKeyCode;
	m_backwarKeyCode = backwardKeyCode;
	m_strafeLeftKeyCode = strafeLeftKeyCode;
	m_strafeRightKeyCode = strafeRightKeyCode;
}

void Camera::update(const std::function<bool(int)>& keyInputFunc,
	const std::function<glm::i32vec2()>& getCursorPosFunc,
	const std::function<void(const glm::i32vec2&)>& setCursorPosFunc,
	const std::function<float(float)>& speedCorrectionFunc)
{
	if (keyInputFunc(m_forwardKeyCode)) {
		moveBy(speedCorrectionFunc(m_moveSpeed));
	}
	if (keyInputFunc(m_backwarKeyCode)) {
		moveBy(speedCorrectionFunc(-m_moveSpeed));
	}
	if (keyInputFunc(m_strafeLeftKeyCode)) {
		strafeBy(speedCorrectionFunc (-m_moveSpeed));
	}
	if (keyInputFunc(m_strafeRightKeyCode)) {
		strafeBy(speedCorrectionFunc(m_moveSpeed));
	}
	const auto currentMousePosition = getCursorPosFunc();
	const auto delta = m_windowCenterPosition - currentMousePosition;

	if (delta.x != 0) {
		rotateLeftRight(static_cast<float>(delta.x) * m_mouseSensitivity);
	}
	if (delta.y != 0) {
		rotateUpDown(static_cast<float>(delta.y) * m_mouseSensitivity);
	}
	setCursorPosFunc(m_windowCenterPosition);
}

void Camera::setWindowCenterPosition(const glm::i32vec2& windowCenterPosition) {
	m_windowCenterPosition = windowCenterPosition;
}

glm::vec3 Camera::getNormalizedViewVector() const {
	return glm::normalize(m_viewPoint - m_position);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_position, m_viewPoint, m_upVector);
}

void Camera::moveBy(float distance) {
	glm::vec3 offset = getNormalizedViewVector();
	offset *= distance;
	m_position += offset;
	m_viewPoint += offset;
}

void Camera::strafeBy(float distance) {
	glm::vec3 strafeVector = glm::normalize(glm::cross(getNormalizedViewVector(), m_upVector));
	strafeVector = glm::normalize(strafeVector);
	strafeVector *= distance;

	m_position += strafeVector;
	m_viewPoint += strafeVector;
}

void Camera::rotateLeftRight(float angleInDegrees) {
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);
	m_viewPoint = m_position + glm::vec3(rotatedViewVector);
}

void Camera::rotateUpDown(float angleInDegrees) {
	const glm::vec3 viewVector = getNormalizedViewVector();
	const glm::vec3 viewVectorWithoutY = glm::normalize(glm::vec3(viewVector.x, 0.0f, viewVector.z));

	float currentAngleDegrees = glm::degrees(acos(glm::dot(viewVectorWithoutY, viewVector)));
	if (viewVector.y < 0.0f) {
		currentAngleDegrees = -currentAngleDegrees;
	}

	float newAngleDegrees = currentAngleDegrees + angleInDegrees;
	if (newAngleDegrees > -85.0f && newAngleDegrees < 85.0f) {
		glm::vec3 rotationAxis = glm::cross(getNormalizedViewVector(), m_upVector);
		rotationAxis = glm::normalize(rotationAxis);

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), rotationAxis);
		glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);

		m_viewPoint = m_position + glm::vec3(rotatedViewVector);
	}
}
