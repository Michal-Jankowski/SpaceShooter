#include "SetupWindow.h"
#include <glm/gtc/matrix_transform.hpp>

std::map<GLFWwindow*, SetupWindow*> SetupWindow::m_windows;

SetupWindow::SetupWindow() {
	for (auto& keyPressElem : m_keyWasPressed) {
		keyPressElem = false;
	}
}

bool SetupWindow::createWindow(const std::string& title, int majorVersion, int minorVersion, bool showFullscreen) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const auto primaryWindow = glfwGetPrimaryMonitor();
	const auto videoMode = glfwGetVideoMode(primaryWindow);
	auto monitor = m_showFullScreen ? primaryWindow : nullptr;
	auto width = 840;
	auto height = 640;
	m_window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
	if (m_window == nullptr) {
		return false;
	}
	glfwMakeContextCurrent(m_window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glfwSetWindowSizeCallback(m_window, onWindowSizeChangedStatic);
	onWindowSizeChangedInternal(width, height);
	glfwSetMouseButtonCallback(m_window, onMouseButtonPressedStatic);
	glfwSetScrollCallback(m_window, onMouseWheelScrollStatic);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(m_window, onKeyboardButtonPressedStatic);
	m_windows[m_window] = this;
    return true;

}

GLFWwindow* SetupWindow::getWindow() const {
	return m_window;
}

void SetupWindow::runApp() {
	setVerticalSynchronization(true);
	recalculateProjectionMatrix();
	initScene();

	m_lastFrameTime = m_lastFrameTimeFPS = glfwGetTime();

	while (glfwWindowShouldClose(m_window) == 0)
	{
		updateDeltaTimeAndFPS();
		renderScene();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
		updateScene();
	}

	releaseScene();

	glfwDestroyWindow(m_window);
	m_windows.erase(m_windows.find(m_window));

	if (m_windows.empty())
	{
		glfwTerminate();
	}
}

void SetupWindow::updateDeltaTimeAndFPS() {
	const auto currentTime = glfwGetTime();
	m_timeDelta = currentTime - m_lastFrameTime;
	m_lastFrameTime = currentTime;
	m_nextFPS++;

	if (currentTime - m_lastFrameTimeFPS > 1.0)
	{
		m_lastFrameTimeFPS = currentTime;
		m_FPS = m_nextFPS;
		m_nextFPS = 0;
	}
}

void SetupWindow::setVerticalSynchronization(bool enable) {
	glfwSwapInterval(enable ? 1 : 0);
	m_isVerticalSynchronizationEnabled = enable;
}

bool SetupWindow::isVerticalSynchronizationEnabled() const {
	return m_isVerticalSynchronizationEnabled;
}

void SetupWindow::setWireframeMode(bool enable) {
	enable ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	m_isWireFrameModeEnabled = enable;
}

bool SetupWindow::isWireframeModeEnabled() const {
	return m_isWireFrameModeEnabled;
}

bool SetupWindow::isFullScreenEnabled() const {
	return m_showFullScreen;
}

void SetupWindow::setFullScreenMode(bool enable) {
	m_showFullScreen = enable;
}

bool SetupWindow::isCameraUpdateEnabled() const {
	return m_isCameraUpdateEnabled;
}

void SetupWindow::setCameraUpdateEnabled(bool enable) {
	m_isCameraUpdateEnabled = enable;
}

glm::mat4 SetupWindow::getProjectionMatrix() const {
	return m_projectionMatrix;
}

glm::mat4 SetupWindow::getOrthoProjectionMatrix() const {
	return m_orthoMatrix;
}

int SetupWindow::getFPS() const {
	return m_FPS;
}

double SetupWindow::getDeltaTime() const {
	return m_timeDelta;
}

double SetupWindow::getValueByTime(double value) const {
	return getDeltaTime() * value;
}

SetupWindow* SetupWindow::getDefaultWindow() {
	return m_windows.size() == 0 ? nullptr : (*m_windows.begin()).second;

}

int SetupWindow::getScreenWidth() const
{
	return m_screenWidth;
}

int SetupWindow::getScreenHeight() const
{
	return m_screenHeight;
}

glm::ivec2 SetupWindow::getOpenGLCursorPosition() const
{
	double posX, posY;
	glfwGetCursorPos(m_window, &posX, &posY);
	return glm::ivec2(static_cast<int>(posX), 640 - static_cast<int>(posY));
}

bool SetupWindow::keyPressed(int keyCode) const {
	return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool SetupWindow::mouseButtonPressed(int keyCode) const {
    return glfwGetMouseButton(m_window, keyCode) == GLFW_PRESS;
}

bool SetupWindow::keyPressedOnce(int keyCode) {
	bool result = false;

	if (keyPressed(keyCode)) {
		if (!m_keyWasPressed[keyCode]) {
			result = true;
		}
		m_keyWasPressed[keyCode] = true;
	}
	else {
		m_keyWasPressed[keyCode] = false;
	}
	return result;
}

void SetupWindow::closeWindow(bool errorHasOccured) {
	glfwSetWindowShouldClose(m_window, true);
	m_hasErrorOccured = errorHasOccured;
}

bool SetupWindow::errorHasOccured() const {
	return m_hasErrorOccured;
}

void SetupWindow::recalculateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(45.0f, static_cast<float>(m_screenWidth) / static_cast<float>(m_screenHeight), 0.5f, 1500.0f);
	m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth), 0.0f, static_cast<float>(m_screenHeight));
}

void SetupWindow::onWindowSizeChangedInternal(int width, int height) {
	m_screenWidth = width;
	m_screenHeight = height;
	recalculateProjectionMatrix();
	glViewport(0, 0, width, height);
	onWindowSizeChanged(width, height);
}

void SetupWindow::onMouseButtonPressedStatic(GLFWwindow* window, int button, int action, int mods) {
	if (m_windows.count(window) != 0) {
		m_windows[window]->onMouseButtonPressed(button, action);
	}
}

void SetupWindow::onMouseWheelScrollStatic(GLFWwindow* window, double offsetX, double offsetY) {
	if (m_windows.count(window) != 0) {
		m_windows[window]->onMouseWheelScroll(offsetX, offsetY);
	}
}

void SetupWindow::onWindowSizeChangedStatic(GLFWwindow* window, int width, int height) {
	if (m_windows.count(window) != 0) {
		m_windows[window]->onWindowSizeChangedInternal(width, height);
	}
}

void SetupWindow::onKeyboardButtonPressedStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (m_windows.count(window) != 0) {
		m_windows[window]->onKeyboardButtonPressed(key, action);
	}
}
