#pragma once

#include <string>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>

class SetupWindow
{
public:
	SetupWindow();

	bool createWindow(const std::string& title, int majorVersion, int minorVersion, bool showFullscreen = false);
	GLFWwindow* getWindow() const;
	void runApp();

	virtual void initScene() {}
	virtual void renderScene() {}
	virtual void updateScene() {}
	virtual void releaseScene() {}
	virtual void onWindowSizeChanged(int width, int height) {}
	virtual void onMouseWheelScroll(double scrollOffsetX, double scrollOffsetY) {}
	virtual void onMouseButtonPressed(int button, int action) {}

	bool keyPressed(int keyCode) const;
	bool keyPressedOnce(int keyCode);

	void closeWindow(bool errorHasOccured = false);
	bool errorHasOccured() const;
	void setVerticalSynchronization(bool enable);
	bool isVerticalSynchronizationEnabled() const;
	void setWireframeMode(bool enable);
	bool isWireframeModeEnabled() const;
	bool isFullScreenEnabled() const;
	void setFullScreenMode(bool enable);
	bool isCameraUpdateEnabled() const;
	void setCameraUpdateEnabled(bool enable);
    glm::mat4 getProjectionMatrix() const;
	glm::mat4 getOrthoProjectionMatrix() const;
	int getFPS() const;
	double getDeltaTime() const;
	double getValueByTime(double value) const;
	static SetupWindow* getDefaultWindow();
	int getScreenWidth() const;
	int getScreenHeight() const;
	glm::ivec2 getOpenGLCursorPosition() const;
private:
	GLFWwindow* m_window = nullptr;
	glm::mat4 m_projectionMatrix = glm::mat4(0.0);
	glm::mat4 m_orthoMatrix = glm::mat4(0.0);
	int m_screenWidth{ 0 };
	int m_screenHeight{ 0 };
	bool m_keyWasPressed[512] = { false };
	bool m_hasErrorOccured = false;
	bool m_isVerticalSynchronizationEnabled = false;
	bool m_isWireFrameModeEnabled = false;
	bool m_showFullScreen = false;
	bool m_isCameraUpdateEnabled = true;
	double m_lastFrameTime = 0.0;
	double m_lastFrameTimeFPS = 0.0; 
	double m_timeDelta = 0.0; 
	int m_FPS = 0; 
	int m_nextFPS = 0; 
	double m_deltaTime = 0.0;

	void recalculateProjectionMatrix();
	void onWindowSizeChangedInternal(int width, int height);
	static void onMouseButtonPressedStatic(GLFWwindow* window, int button, int action, int mods);
	static void onMouseWheelScrollStatic(GLFWwindow* window, double offsetX, double offsetY);
	static void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height);
	void updateDeltaTimeAndFPS();
	static std::map<GLFWwindow*, SetupWindow*> m_windows;
};