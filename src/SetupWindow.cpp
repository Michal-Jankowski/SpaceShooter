#include "SetupWindow.h"
#include <glm/gtc/matrix_transform.hpp>

std::map<GLFWwindow*, SetupWindow*> SetupWindow::windows;

SetupWindow::SetupWindow() {
	for (auto& kwp : keyWasPressed) {
		kwp = false;
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
	const auto monitor = showFullscreen ? primaryWindow : nullptr;

	window = glfwCreateWindow(videoMode->width, videoMode->height, title.c_str(), monitor, nullptr);
	if (window == nullptr) {
		return false;
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glfwSetWindowSizeCallback(window, onWindowSizeChangedStatic);
	
	if (!showFullscreen){
		glfwMaximizeWindow(window);
		// After calling glfwMaximizeWindow, the onWindowSizeChanged somehow does not get called. Therefore I call it manually.
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		onWindowSizeChangedInternal(width, height);
	}
	glfwSetMouseButtonCallback(window, onMouseButtonPressedStatic);
	glfwSetScrollCallback(window, onMouseWheelScrollStatic);
	windows[window] = this;
	return true;

}

GLFWwindow* SetupWindow::getWindow() const
{
	return window;
}

void SetupWindow::runApp() {
	setVerticalSynchronization(true);
	recalculateProjectionMatrix();
	initScene();

	lastFrameTime = lastFrameTimeFPS = glfwGetTime();

	while (glfwWindowShouldClose(window) == 0)
	{
		updateDeltaTimeAndFPS();
		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
		updateScene();
	}

	releaseScene();

	glfwDestroyWindow(window);
	windows.erase(windows.find(window));

	if (windows.empty())
	{
		glfwTerminate();
	}
}

void SetupWindow::updateDeltaTimeAndFPS()
{
	const auto currentTime = glfwGetTime();
	timeDelta = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
	nextFPS++;

	if (currentTime - lastFrameTimeFPS > 1.0)
	{
		lastFrameTimeFPS = currentTime;
		FPS = nextFPS;
		nextFPS = 0;
	}
}

void SetupWindow::setVerticalSynchronization(bool enable)
{
	glfwSwapInterval(enable ? 1 : 0);
	isVerticalSynchronizationEnabled = enable;
}

bool SetupWindow::keyPressed(int keyCode) const {
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

bool SetupWindow::keyPressedOnce(int keyCode) {
	bool result = false;

	if (keyPressed(keyCode)) {
		if (!keyWasPressed[keyCode]) {
			result = true;
		}
		keyWasPressed[keyCode] = true;
	}
	else {
		keyWasPressed[keyCode] = false;
	}
	return result;
}

void SetupWindow::closeWindow(bool errorHasOccured) {
	glfwSetWindowShouldClose(window, true);
	hasErrorOccured = errorHasOccured;
}

bool SetupWindow::errorHasOccured() const {
	return hasErrorOccured;
}

void SetupWindow::recalculateProjectionMatrix() {
	int width, height;
	glfwGetWindowSize(getWindow(), &width, &height);
	projectionMatrix = glm::perspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.5f, 1500.0f);
	orthoMatrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

void SetupWindow::onWindowSizeChangedInternal(int width, int height) {
	recalculateProjectionMatrix();
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
	onWindowSizeChanged(width, height);
}

void SetupWindow::updateDeltaTime() {
}

void SetupWindow::onMouseButtonPressedStatic(GLFWwindow* window, int button, int action, int mods) {
	if (windows.count(window) != 0) {
		windows[window]->onMouseButtonPressed(button, action);
	}
}

void SetupWindow::onMouseWheelScrollStatic(GLFWwindow* window, double offsetX, double offsetY) {
	if (windows.count(window) != 0) {
		windows[window]->onMouseWheelScroll(offsetX, offsetY);
	}
}

void SetupWindow::onWindowSizeChangedStatic(GLFWwindow* window, int width, int height) {
	if (windows.count(window) != 0) {
		windows[window]->onWindowSizeChangedInternal(width, height);
	}
}