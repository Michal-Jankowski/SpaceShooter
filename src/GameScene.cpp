#include "GameScene.h"

// Render using triangle strip!
glm::vec3 plainGroundVertices[] =
{
	glm::vec3(-200.0f, 0.0f, -200.0f), // Left-back point
	glm::vec3(-200.0f, 0.0f, 200.0f), // Left-front point
	glm::vec3(200.0f, 0.0f, -200.0f), // Right-back point
	glm::vec3(200.0f, 0.0f, 200.0f) // Right-front point
};

GLuint plainGroundIndices[] = {
	0, 1, 3,
	1, 2, 3
};

glm::vec2 plainGroundTexCoords[] =
{
	glm::vec2(0.0f, 20.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(20.0f, 20.0f),
	glm::vec2(20.0f, 0.0f)
};

glm::vec3 plainGroundColors[] =
{
	glm::vec3(0.0f, 0.5f, 0.0f),
	glm::vec3(0.0f, 0.85f, 0.0f),
	glm::vec3(0.0f, 0.35f, 0.25f),
	glm::vec3(0.0f, 0.8f, 0.2f)
};

// Render using triangle strip!
glm::vec2 quad2D[] =
{
	glm::vec2(0, 1), // Top-left point
	glm::vec2(0, 0), // Bottom-left point
	glm::vec2(1, 1), // Top-right point
	glm::vec2(1, 0) // Bottom-right point
};

void GameScene::initScene() {
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);
	// load shaders
	m_vsShader.loadShaderFromFile("../src/shaders/shader.vs", GL_VERTEX_SHADER);
	m_fsShader.loadShaderFromFile("../src/shaders/shader.fs", GL_FRAGMENT_SHADER);
	m_vsGround.loadShaderFromFile("../src/shaders/ground.vs", GL_VERTEX_SHADER);
	m_fsGround.loadShaderFromFile("../src/shaders/ground.fs", GL_FRAGMENT_SHADER);

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
	m_vertexEBO.createVBO(); // create EBO
	m_vertexBuffer.bindVBO();
	m_vertexBuffer.addRawData(plainGroundVertices, sizeof(plainGroundVertices));
	m_vertexBuffer.uploadDataToGPU(GL_STATIC_DRAW);
	// use EBO
	m_vertexEBO.bindVBO(GL_ELEMENT_ARRAY_BUFFER);
	m_vertexEBO.addRawData(plainGroundIndices, sizeof(plainGroundIndices));
	m_vertexEBO.uploadDataToGPU(GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	m_textureBuffer.createVBO();
	m_textureBuffer.bindVBO();
	m_textureBuffer.addRawData(plainGroundTexCoords, sizeof(plainGroundTexCoords));
	m_textureBuffer.uploadDataToGPU(GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<void*>(0));

	/// UNBINDING VBO, VAO, EBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinding VBO, but dont have to
	glBindVertexArray(0); // we can unbind VAO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // we should not unbind EBO while VAO is active, but dont have to
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	m_snowTexture.loadTexture2D("../res/img/lava.png", true);

	m_sampler.create(true);
	m_sampler.bind();
	m_sampler.setFilterOptions(FilterOptions::MIN_FILTER_TRILINEAR, GL_TEXTURE_MIN_FILTER);
	m_sampler.setFilterOptions(FilterOptions::MAG_FILTER_BILINEAR, GL_TEXTURE_MAG_FILTER);

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
	std::string title = "SpaceShooter FPS count: " + std::to_string(getFPS()) + " VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off"); 
	glfwSetWindowTitle(getWindow(), title.c_str());

	m_camera->update(
		[this](int keyCode) {return this->keyPressed(keyCode); },
		[this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); },
		[this](float value) { return this->getValueByTime(value); });
}

void GameScene::releaseScene() {

	m_mainProgram.deleteProgram();
	m_vsShader.deleteShader();
	m_fsShader.deleteShader();
	m_vertexBuffer.deleteVBO();
	m_vertexEBO.deleteVBO();
	m_textureBuffer.deleteVBO();
	m_snowTexture.deleteTexture();
	m_sampler.deleteSampler();
	glDeleteVertexArrays(1, &m_VAO);
}
