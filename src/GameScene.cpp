#include "GameScene.h"
#include "../src/ShaderManager.h"
#include "../src/ShaderProgramManager.h"
#include "../src/TextureManager.h"
#include "../src/SamplerManager.h"
#include "../src/MatrixManager.h"
#include <glm/gtc/matrix_transform.hpp>


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

std::vector<glm::vec3> cratePositions
{
	glm::vec3(-30.0f, 0.0f, -80.0f),
	glm::vec3(30.0f, 0.0f, -40.0f),
	glm::vec3(-30.0f, 0.0f, 0.0f),
	glm::vec3(30.0f, 0.0f, 40.0f),
	glm::vec3(-30.0f, 0.0f, 80.0f),
};

float rotationAngleRad = 0.0f;


void GameScene::initScene() {

	try {
		auto& shaderManager = ShaderManager::getInstance();
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& textureManager = TextureManager::getInstance();

		shaderManager.loadFragmentShader("main_part", "src/shaders/shader.frag");
		shaderManager.loadVertexShader("main_part", "src/shaders/shader.vert");

		//shaderManager.loadVertexShader("normals", "src/shaders/normals.vert");
		//shaderManager.loadFragmentShader("normals", "src/shaders/normals.frag");

		auto& mainShaderProgram = shaderProgramManager.createShaderProgram("main");
		mainShaderProgram.addShaderToProgram(shaderManager.getVertexShader("main_part"));
		mainShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("main_part"));

		//auto& normalsShaderProgram = shaderProgramManager.createShaderProgram("normals");
		//normalsShaderProgram.addShaderToProgram(shaderManager.getVertexShader("normals"));
		//normalsShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("normals"));
		// init skybox
		m_skybox = std::make_unique<Skybox>("res/skybox/blue", true, true, true);

		SamplerManager::getInstance().createSampler("main", FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_TRILINEAR);
		TextureManager::getInstance().loadTexture2D("snow", "res/img/snow.png");
		TextureManager::getInstance().loadTexture2D("lava", "res/img/lava.png");


		m_cube = std::make_unique<Cube>(true, true, true);

		shaderProgramManager.linkAllPrograms();

		int width, height;
		glfwGetWindowSize(getWindow(), &width, &height);
		m_camera = std::make_unique<Camera>(glm::vec3(-120.0f, 8.0f, 120.0f), glm::vec3(-120.0f, 8.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.f), glm::i32vec2(width / 2, height / 2), 15.0f);
		m_ambientLight = std::make_unique<AmbientLight>(glm::vec3(0.6f, 0.6f, 0.6f));
		m_diffuseLight = std::make_unique<DiffuseLight>(glm::vec3(1.0f, 1.0f, 1.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), 15.0f);

	}
	catch (const std::runtime_error& error) {
		std::cout << "Error occured during initialization: " << error.what() << std::endl;
		closeWindow(true);
		return;
	}
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);
	/*
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

	m_snowTexture.loadTexture2D("res/img/snow.png", true);

	m_sampler.create(true);
	m_sampler.bind();
	m_sampler.setFilterOptions(FilterOptions::MIN_FILTER_TRILINEAR, GL_TEXTURE_MIN_FILTER);
	m_sampler.setFilterOptions(FilterOptions::MAG_FILTER_BILINEAR, GL_TEXTURE_MAG_FILTER);
	*/
	

}

void GameScene::renderScene() {

	auto& matrixManager = MatrixManager::getInstance();
	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& textureManager = TextureManager::getInstance();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matrixManager.setProjectionMatrix(getProjectionMatrix());
	matrixManager.setOrthoProjectionMatrix(getOrthoProjectionMatrix());
	matrixManager.setViewMatrix(m_camera->getViewMatrix());

	auto& mainProgram = shaderProgramManager.getShaderProgram("main");
	mainProgram.useProgram();
	mainProgram.setUniform("matrices.projectionMatrix", getProjectionMatrix());
	mainProgram.setUniform("matrices.viewMatrix", m_camera->getViewMatrix());
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
	mainProgram.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
	const int samplerValue = 0;
	std::string sampler = "sampler";
	int iLoc = glGetUniformLocation(mainProgram.getProgramID(), sampler.c_str());
	if (iLoc == -1) {
		std::cerr << "ERROR: uniform with this name " << sampler.c_str() << " dose not exists, it will fail" << std::endl;
	}
	glUniform1iv(iLoc, 1, (GLint*)&samplerValue);
	//mainProgram.setUniform("sampler", samplerValue);

	AmbientLight  ambientSkybox(glm::vec3(0.1f, 0.6f, 0.6f));
	//DiffuseLight::none().setUniform(mainProgram, "diffuseLight");
	//ambientSkybox.setUniform(mainProgram, "ambientLight");

	// render skybox
	//m_ambientLight->setUniform(mainProgram, "ambientLight");
	//m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	m_skybox->render(m_camera->getEye(), mainProgram);

	SamplerManager::getInstance().getSampler("main").bind();
	//m_ambientLight->setUniform(mainProgram, "ambientLight");
	//m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	
	std::vector<glm::mat4> crateModelMatrices;
	for (const auto& position : cratePositions)
	{
		const auto crateSize = 8.0f;
		auto model = glm::translate(glm::mat4(1.0f), position);
		float renderedHeight = 5.0f;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f + crateSize / 2.0f + renderedHeight, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(crateSize, crateSize, crateSize));
		crateModelMatrices.push_back(model);
		mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", model);

		TextureManager::getInstance().getTexture("lava").bind(0);
		m_cube->render();
	}
}

void GameScene::updateScene() {

	std::string title = "SpaceShooter FPS count: " + std::to_string(getFPS()) + " VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off");
	glfwSetWindowTitle(getWindow(), title.c_str());

	if (keyPressedOnce(GLFW_KEY_ESCAPE)) {
		closeWindow();
	}
	
	if (keyPressedOnce(GLFW_KEY_0)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}

	if (keyPressedOnce(GLFW_KEY_1)) {
		setWireframeMode(!isWireframeModeEnabled());
	}

	if (keyPressedOnce(GLFW_KEY_2)) {
		setCameraUpdateEnabled(!isCameraUpdateEnabled());
	}

	if (isCameraUpdateEnabled()) {
		m_camera->update([this](int keyCode) {return this->keyPressed(keyCode); }, [this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); }, [this](float value) { return this->getValueByTime(value); });
	}

	rotationAngleRad += getValueByTime(glm::radians(45.0f));

}

void GameScene::releaseScene() {

	m_skybox.reset();
	ShaderManager::getInstance().clearShaderCache();
	ShaderProgramManager::getInstance().clearShaderProgramCache();
	TextureManager::getInstance().clearTextureCache();
	SamplerManager::getInstance().clearSamplerKeys();
	m_cube.reset();
}
