#include <iostream>
#include "../../game/GameScene.h"
#include "../shaders/Shader.h"
#include "../shaders/ShaderProgram.h"

int main(void) {
	const std::string& windowTitle = "SpaceShooter";
	int majorVersion = 4;
	int minorVersion = 6;
	GameScene gameScene;
	if (!gameScene.createWindow(windowTitle, majorVersion, minorVersion))
	{
		printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
		return 1;
	}
	gameScene.runApp();

}
