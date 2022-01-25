#include <iostream>
#include <array>
#include "../../game/GameScene.h"
#include "../shaders/Shader.h"
#include "../shaders/ShaderProgram.h"

int main(void) {
	std::array<size_t, 2> windowVersion{4, 6};

	GameScene gameScene;
	if (!gameScene.createWindow("SpaceShooter", windowVersion[0], windowVersion[1])) {
		throw std::runtime_error("Failed to create window with OpenGL context");
	}
	gameScene.runApp();

}
