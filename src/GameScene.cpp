#include "GameScene.h"
void GameScene::initScene() {
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);
	// load shaders
	m_vsShader.loadShaderFromFile("shader.vs", GL_VERTEX_SHADER);
	m_fsShader.loadShaderFromFile("shader.fs", GL_FRAGMENT_SHADER);

	if (!m_vsShader.hasLoaded() || !m_fsShader.hasLoaded()) {
		closeWindow(true);
		return;
	}
	// load vs & fs to mainProgram
	m_mainProgram.createProgram();
	m_mainProgram.addShaderToProgram(m_vsShader);
	m_mainProgram.addShaderToProgram(m_fsShader);

	if (!m_mainProgram.linkProgram()) {
		closeWindow(true);
		return;
	}
	// one VAO array
	glGenVertexArrays(1, &m_VAO); 
	glBindVertexArray(m_VAO);

	glm::vec3 mightyTriangle[] = { glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) };

	m_VBOBuffer.createVBO();
	m_VBOBuffer.bindVBO();
	m_VBOBuffer.addData(mightyTriangle);
	m_VBOBuffer.uploadDataToGPU(GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
}

void GameScene::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_mainProgram.useProgram();
	glBindVertexArray(m_VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GameScene::updateScene() {
	if (keyPressedOnce(GLFW_KEY_ESCAPE)) {
		closeWindow();
	}
}

void GameScene::releaseScene() {

	m_mainProgram.deleteProgram();
	m_vsShader.deleteShader();
	m_fsShader.deleteShader();
	m_VBOBuffer.deleteVBO();
	glDeleteVertexArrays(1, &m_VAO);
}
