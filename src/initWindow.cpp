#include <iostream>
#include "../src/GameScene.h"
#include "../src/Shader.h"
#include "../src/ShaderProgram.h"

int main(void) {
	const std::string& windowTitle = "SpaceShooter";
	int majorVersion = 4;
	int minorVersion = 4;
	GameScene gameScene;
	if (!gameScene.createWindow(windowTitle, majorVersion, minorVersion))
	{
		printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
		return 1;
	}
	gameScene.runApp();

}
