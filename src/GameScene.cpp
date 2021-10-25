#include "GameScene.h"
void GameScene::initScene() {
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);
	// load shaders
	m_vsShader.loadShaderFromFile("shader.vs", GL_VERTEX_SHADER);
	m_fsShader.loadShaderFromFile("shader.fs", GL_FRAGMENT_SHADER);
	m_vsGround.loadShaderFromFile("ground.vs", GL_VERTEX_SHADER);
	m_fsGround.loadShaderFromFile("ground.fs", GL_FRAGMENT_SHADER);
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

	if (!m_vsGround.hasLoaded() || !m_fsGround.hasLoaded()) {
		closeWindow(true);
		return;
	}
	m_groundProgram.createProgram();
	m_groundProgram.addShaderToProgram(m_vsGround);
	m_groundProgram.addShaderToProgram(m_fsGround);

	if (!m_groundProgram.linkProgram()) {
		closeWindow(true);
		return;
	}

	
	// one VAO array
	glGenVertexArrays(1, &m_VAO); 
	glBindVertexArray(m_VAO);

	m_vertexBuffer.createVBO();
	m_vertexBuffer.bindVBO();
	m_vertexBuffer.addRawData(static_cast<void*>(m_staticGeometry.getPlainVertices().data()), sizeof(m_staticGeometry.getPlainVertices()));
	m_vertexBuffer.uploadDataToGPU(GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(0));

	m_textureBuffer.createVBO();
	m_textureBuffer.bindVBO();
	m_textureBuffer.addRawData(static_cast<void*>(m_staticGeometry.getPlainTexCoords().data()), sizeof(m_staticGeometry.getPlainTexCoords()));
	m_textureBuffer.uploadDataToGPU(GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<void*>(0));

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	m_snowTexture.loadTexture2D("res/img/snow.png");

	m_sampler.create();
	m_sampler.bind();
	m_sampler.setFilterOptions(FilterOptions::MAG_FILTER_BILINEAR);
	m_sampler.setFilterOptions(FilterOptions::MIN_FILTER_TRILINEAR);

	int posX, posY, width, height;
	glfwGetWindowPos(getWindow(), &posX, &posY);
	glfwGetWindowPos(getWindow(), &width, &height);
	m_camera = std::make_unique<Camera>(glm::vec3(-120.0f, 8.0f, 120.0f), glm::vec3(-120.0f, 8.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.f), glm::i32vec2(posX + width / 2, posY + height / 2), 15.0f);

}

void GameScene::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_groundProgram.useProgram();
	glBindVertexArray(m_VAO);

	m_groundProgram.setUniform("matrices.projectionMatrix", getProjectionMatrix());
	m_groundProgram.setUniform("matrices.viewMatrix", m_camera->getViewMatrix());

	m_groundProgram.setUniform("matrices.modelMatrix", glm::mat4(1.0));

	m_snowTexture.bind(0);
	m_sampler.bind(0);
	m_groundProgram.setUniform("snowSampler", 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_mainProgram.useProgram();
	m_mainProgram.setUniform("matrices.projectionMatrix", getProjectionMatrix());
	m_mainProgram.setUniform("matrices.viewMatrix", m_camera->getViewMatrix());
	m_mainProgram.setUniform("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

}

void GameScene::updateScene() {
	if (keyPressedOnce(GLFW_KEY_ESCAPE)) {
		closeWindow();
	}
	
	if (keyPressedOnce(GLFW_KEY_0)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}

	if (keyPressedOnce(GLFW_KEY_1)) {
		setWireframeMode(!isWireframeModeEnabled());
	}

	glfwSetWindowTitle(getWindow(), "SpaceShooter");

	m_camera->update([this](int keyCode) {return this->keyPressed(keyCode); },
		[this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y);});

}

void GameScene::releaseScene() {

	m_mainProgram.deleteProgram();
	m_vsShader.deleteShader();
	m_fsShader.deleteShader();
	m_vertexBuffer.deleteVBO();
	m_snowTexture.deleteTexture();
	m_sampler.deleteSampler();
	glDeleteVertexArrays(1, &m_VAO);
}
